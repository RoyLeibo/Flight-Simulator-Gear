//
// Created by roy on 12/17/18.
//

#include "Connect.h"
#include "IO.h"

Connect::Connect(string IP, double port, maps* myMaps) {
    this->IP = IP ; // INPUT CHECK NEEDED
    if (port > 0)
    {
        //need to check if port must be int
        this->port = (int)port;
    }
    this->myMaps = myMaps ;
}

void Connect::execute() {
    struct sockaddr_in serv_addr;
    struct hostent *server;

    myMaps->set_sockfd(socket(AF_INET, SOCK_STREAM, 0)); // calling to socket function

    if (myMaps->get_sockfd() < 0) { // if the function failed, print error
        perror("cannot open socket, please try again");
        exit(1);
    }

    server = gethostbyname(this->IP.c_str()); // update the IP address to connect

    if (server == NULL) { // if IP update is failed, print error
        fprintf(stderr,"cannot locate host\n");
        exit(0);
    }

    // update socket's data
    bzero((char *) &serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    bcopy((char *)server->h_addr, (char *)&serv_addr.sin_addr.s_addr, server->h_length);
    serv_addr.sin_port = htons(this->port);

    cout << "connecting" << endl ;
    // connect to server, if failed print error
    if (connect(myMaps->get_sockfd(), (struct sockaddr*)&serv_addr, sizeof(serv_addr)) < 0) {
        perror("cannot connect to server");
        exit(1);
    }

    cout << "opening thread" << endl ;
    open_thread() ;
}

// initialize the thread struct and create a new thread

void Connect::open_thread() {

    // after connection has established, initialize a thread for reading data from the simulator
    pthread_t tid ;
    pthread_attr_t attr ;
    pthread_attr_init(&attr) ;

    cout << "i am inside open thread func" << endl ;

    // create a thread with the struct and a function which reads data from the simulator,
    // parse it and update the variables map
    pthread_create(&tid, &attr, run_write_to_simulator, this->myMaps) ;
}

void* run_write_to_simulator(void* arg) {
    maps* myMaps = (maps*) arg ;
    cout << "inside thread!!" << endl ;
    IO().write_to_simulator(myMaps) ;
    pthread_exit(0) ;
}

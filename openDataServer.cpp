//
// Created by roy on 12/17/18.
//

#include "openDataServer.h"

// Function that is operates in the thread which receives data from simulator.
// The function calls "read_from_simulator" function which reads the data is
// sent from the simulator

void* run_read_from_simulator(void* arg) {
    struct read_struct* arg_struct = (read_struct*)arg ;
    cout << "I am inside thread" << endl ;
    IO().read_from_simulator(arg_struct->newsockfd, arg_struct->hz, arg_struct->myMaps) ;
    pthread_t exit(0) ;
}

openDataServer::openDataServer(double port, double hz, maps* myMaps) {
    if (port > 0) { // INPUT CHECK NEEDED
        this->port = port;
    }
    if (hz > 0) {
        this->hz = hz;
    }
    this->myMaps = myMaps ;
}

void openDataServer::execute() {
    int newsockfd, clilen;
    struct sockaddr_in serv_addr, cli_addr;

    myMaps->set_sockfd1(socket(AF_INET, SOCK_STREAM, 0)); // calling to socket function

    if (myMaps->get_sockfd1() < 0) { // if the function failed, print error
        perror("cannot open socket, please try again");
        exit(1);
    }

    bzero((char *) &serv_addr, sizeof(serv_addr)); // initialize the socket struct

    // update socket's data
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port = htons(this->port);

    cout << "binding " << endl ;

    if (bind(myMaps->get_sockfd1(), (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0) { // binding host address
        perror("cannot bind to server");
        exit(1);
    }

    cout << "listeing" << endl ;

    listen(myMaps->get_sockfd1(),1); // wait for a connection request
    clilen = sizeof(cli_addr);

    // accept the connection request
    newsockfd = accept(myMaps->get_sockfd1(), (struct sockaddr *)&cli_addr, (socklen_t*)&clilen);

    cout << "accepting" << endl ;
    if (newsockfd < 0) { // if connection failed, print error
        perror("cannot accept your connection request");
        exit(1);
    }
    cout << "opening thread" << endl ;
    /*char c[1] ;
    bzero(c, 1) ;
    while ((read(sockfd, c, 1) < 0)) {}*/
    open_thread(newsockfd);
}

// initialize the thread struct and create a new thread

void openDataServer::open_thread(int newsockfd) {

    // after connection has established, initialize a thread for reading data from the simulator
    pthread_t tid ;
    pthread_attr_t attr ;
    pthread_attr_init(&attr) ;

    // initialize struct
    struct read_struct r_s ;
    r_s.newsockfd = newsockfd ;
    r_s.myMaps = myMaps ;
    r_s.hz = hz ;

    cout << "creating thread" << endl ;

    // create a thread with the struct and a function which reads data from the simulator,
    // parse it and update the variables map
    pthread_create(&tid, &attr, run_read_from_simulator, &r_s) ;
}


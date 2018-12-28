//
// Created by roy on 12/17/18.
//

#include "openDataServer.h"

// Function that is operates in the thread which receives data from simulator.
// The function calls "read_from_simulator" function which reads the data is
// sent from the simulator

void* run_read_from_simulator(void* arg) {
    struct read_struct* arg_struct = (read_struct*)arg ;
    IO().read_from_simulator(arg_struct->new_sock_fd, arg_struct->hz, arg_struct->s_maps) ;
    pthread_t exit(0) ;
}

openDataServer::openDataServer(double port, double hz, maps* s_maps) {
    if (port > 0) { // INPUT CHECK NEEDED
        this->port = port;
    }
    if (hz > 0) {
        this->hz = hz;
    }
    this->s_maps = s_maps ;
}

/* this function open a new server using socket and connects 
 * to the simulator.
 */

void openDataServer::execute() {
    int sockfd, clilen;
    struct sockaddr_in serv_addr, cli_addr;

    sockfd = socket(AF_INET, SOCK_STREAM, 0); // calling to socket function

    if (sockfd < 0) { // if the function failed, print error
        perror("cannot open socket, please try again");
        exit(1);
    }

    bzero((char *) &serv_addr, sizeof(serv_addr)); // initialize the socket struct

    // update socket's data
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port = htons(this->port);


    if (bind(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0) { // binding host address
        perror("cannot bind to server");
        exit(1);
    }

    cout << "listening" << endl ;

    listen(sockfd,1); // wait for a connection request
    clilen = sizeof(cli_addr);

    // accept the connection request
    s_maps->set_sockfd1(accept(sockfd, (struct sockaddr *)&cli_addr, (socklen_t*)&clilen));

    cout << "accepting" << endl ;
    if (s_maps->get_sockfd1() < 0) { // if connection failed, print error
        perror("cannot accept your connection request");
        exit(1);
    }

    cout << "opening thread" << endl ;
    open_thread(s_maps->get_sockfd1());
}

// initialize the thread struct and create a new thread

void openDataServer::open_thread(int new_sock_fd) {

    // after connection has established, initialize a thread for reading data from the simulator
    pthread_t tid ;
    pthread_attr_t attr ;
    pthread_attr_init(&attr) ;

    // initialize struct
    struct read_struct r_s ;
    r_s.new_sock_fd = new_sock_fd ;
    r_s.s_maps = s_maps ;
    r_s.hz = hz ;

    cout << "creating thread" << endl ;

    // create a thread with the struct and a function which reads data from the simulator,
    // parse it and update the variables map
    pthread_create(&tid, &attr, run_read_from_simulator, &r_s) ;
}


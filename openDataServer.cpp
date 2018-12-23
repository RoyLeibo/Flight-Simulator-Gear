//
// Created by roy on 12/17/18.
//

#include "openDataServer.h"

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
    int sockfd, newsockfd, clilen;
    struct sockaddr_in serv_addr, cli_addr;
    IO io ;

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

    listen(sockfd,1); // wait for a connection request
    clilen = sizeof(cli_addr);

    // accept the connection request
    newsockfd = accept(sockfd, (struct sockaddr *)&cli_addr, (socklen_t*)&clilen);

    if (newsockfd < 0) { // if connection failed, print error
        perror("cannot accept your connection request");
        exit(1);
    }

    // after connection has established, call the "IO" class for start reading data
    io.read_from_simulator(newsockfd, this->myMaps, hz) ;
}

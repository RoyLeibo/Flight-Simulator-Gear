//
// Created by roy on 12/17/18.
//

#include "Connect.h"

Connect::Connect(string IP, double port, IO* io) {
    this->IP = IP ; // INPUT CHECK NEEDED
    if (port > 0)
    {
        //need to check if port must be int
        this->port = (int)port;
    }
}

void Connect::execute() {
    int portno;
    struct sockaddr_in serv_addr;
    struct hostent *server;

    g_sockfd = socket(AF_INET, SOCK_STREAM, 0); // calling to socket function

    if (g_sockfd < 0) { // if the function failed, print error
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

    // connect to server, if failed print error
    if (connect(g_sockfd, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) < 0) {
        perror("cannot connect to server");
        exit(1);
    }
}

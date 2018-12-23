//
// Created by roy on 12/17/18.
//

#include "connect.h"

connect::connect(string IP, double port, IO* io) {
    this->IP = IP ; // INPUT CHECK NEEDED
    if (port > 0)
    {
        //need to check if port must be int
        this->port = (int)port;
    }
}

void connect::execute() {
    int sockfd, portno;
    struct sockaddr_in serv_addr;
    struct hostent *server;

    char buffer[256] ;
    bzero(buffer,256);
    string s = "set controls/flight/rudder 1\r\n" ;
    for (int i = 0; i < s.length() ; i++) {
        buffer[i] = s[i] ;
    }

    portno = this->port;

    /* Create a socket point */
    sockfd = socket(AF_INET, SOCK_STREAM, 0);

    if (sockfd < 0) {
        perror("ERROR opening socket");
        exit(1);
    }

    server = gethostbyname(this->IP.c_str());

    if (server == NULL) {
        fprintf(stderr,"ERROR, no such host\n");
        exit(0);
    }

    bzero((char *) &serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    bcopy((char *)server->h_addr, (char *)&serv_addr.sin_addr.s_addr, server->h_length);
    serv_addr.sin_port = htons(portno);

    /* Now connect to the server */
    if (connect(sockfd, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) < 0) {
        perror("ERROR connecting");
        exit(1);
    }


}

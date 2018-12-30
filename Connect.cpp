//
// Created by roy on 12/17/18.
//

#include "Connect.h"
#include "IO.h"

Connect::Connect(string IP, double port, maps* s_maps) {
    this->IP = IP ; // INPUT CHECK NEEDED
    if (port > 0)
    {
        //need to check if port must be int
        this->port = (int)port;
    }
    this->s_maps = s_maps ;
}

/* this function connect to the simulator as a client using socket
 */

void Connect::execute() {
    struct sockaddr_in serv_addr;
    struct hostent *server;

    s_maps->set_sockfd2(socket(AF_INET, SOCK_STREAM, 0)); // calling to socket function

    if (s_maps->get_sockfd2() < 0) { // if the function failed, print error
        perror("cannot open socket, please try again");
        exit(1);
    }

    server = gethostbyname(this->IP.c_str()); // update the IP address to connect

    if (server == NULL) { // if IP update is failed, print error
        fprintf(stderr, "cannot locate host\n");
        exit(0);
    }

    // update socket's data
    bzero((char *) &serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    bcopy((char *) server->h_addr, (char *) &serv_addr.sin_addr.s_addr, server->h_length);
    serv_addr.sin_port = htons(this->port);

    cout << "connecting" << endl;

    // connect to server, if failed print error
    if (connect(s_maps->get_sockfd2(), (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0) {
        perror("cannot connect to server");
        exit(1);
    }
}

Connect::~Connect(){}

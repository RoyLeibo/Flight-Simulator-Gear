//
// Created by roy on 12/17/18.
//

#include "connect.h"

connect::connect(string IP, double port) {
    this->IP = IP ; // INPUT CHECK NEEDED
    if (port > 0)
    {
        //need to check if port must be int
        this->port = (int)port;
    }
}

void connect::execute() {

    // CONNECT TO SOCKET

}

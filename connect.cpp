//
// Created by roy on 12/17/18.
//

#include "connect.h"

connect::connect(int IP, int port) {
    this->IP = IP ; // INPUT CHECK NEEDED
    if (port > 0) {
        this->port = port;
    }
}

void connect::execute() {

    // CONNECT TO SOCKET

}

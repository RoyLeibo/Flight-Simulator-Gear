//
// Created by roy on 12/17/18.
//

#include "openDataServer.h"

openDataServer::openDataServer(int port, int hz) {
    if (port > 0) {
        this->port = port;
    }
    if (hz > 0) {
        this->hz = hz;
    }
}

void openDataServer::execute() {

    // OPEN SOCKET

}

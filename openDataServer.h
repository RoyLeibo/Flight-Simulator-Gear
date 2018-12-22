//
// Created by roy on 12/17/18.
//

#ifndef UNTITLED11_OPENDATASERVER_H
#define UNTITLED11_OPENDATASERVER_H

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <netdb.h>
#include <unistd.h>
#include <netinet/in.h>
#include <string.h>
#include <sys/socket.h>
#include "command.h"
#include "IO.h"
#include "maps.h"

class openDataServer: public command {
    private:
        double port ;
        double hz ;
    public:
        openDataServer(double port, double hz) ;
        virtual void execute() ;

};


#endif //UNTITLED11_OPENDATASERVER_H

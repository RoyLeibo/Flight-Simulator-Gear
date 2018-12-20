//
// Created by roy on 12/17/18.
//

#ifndef UNTITLED11_OPENDATASERVER_H
#define UNTITLED11_OPENDATASERVER_H

#include "command.h"

class openDataServer: public command {

    int port ;
    int hz ;

    openDataServer(int port, int hz) ;
    void execute() ;

};


#endif //UNTITLED11_OPENDATASERVER_H

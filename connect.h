//
// Created by roy on 12/17/18.
//

#ifndef UNTITLED11_CONNECT_H
#define UNTITLED11_CONNECT_H

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <netdb.h>
#include <sys/socket.h>
#include <unistd.h>
#include <netinet/in.h>
#include <string.h>
#include "command.h"
#include "IO.h"

class connect : public command{

    string IP ;
    int port ;

    connect(string IP, double port, IO* io) ;
    virtual void execute() ;

};


#endif //UNTITLED11_CONNECT_H

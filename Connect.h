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
#include "maps.h"

void* run_write_to_simulator(void* arg) ;

class Connect : public command{

    string IP ;
    int port ;
    maps* myMaps ;

public:
    Connect(string IP, double port, maps* myMaps) ;
    virtual void execute() ;
    void open_thread() ;

};



#endif //UNTITLED11_CONNECT_H

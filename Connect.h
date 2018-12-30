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
#include "Command.h"
#include "Maps.h"

void* run_write_to_simulator(void* arg) ;

class Connect : public Command{

    string IP ;
    int port ;
    maps* s_maps ;

public:
    Connect(string IP, double port, maps* s_maps) ;
    virtual void execute() ;
    void open_thread() ;
    ~Connect() ;

};



#endif //UNTITLED11_CONNECT_H

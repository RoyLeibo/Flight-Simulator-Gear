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
#include <pthread.h>
#include "Command.h"
#include "IO.h"
#include "Maps.h"

void* run_read_from_simulator(void* arg) ;

class openDataServer: public Command {
    private:
        double port ;
        double hz ;
        maps* s_maps ;

    public:
        openDataServer(double port, double hz, maps* s_maps) ;
        virtual void execute() ;
        void open_thread(int new_sock_fd) ;

};

// struct for the the thread that receives data from the simulator
// and updates the variables maps

struct read_struct {
    maps* s_maps ;
    int new_sock_fd ;
    int hz ;

};


#endif //UNTITLED11_OPENDATASERVER_H

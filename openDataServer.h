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
#include "command.h"
#include "IO.h"
#include "maps.h"

void* run_read_from_simulator(void* arg) ;

class openDataServer: public command {
    private:
        double port ;
        double hz ;
        maps* myMaps ;

    public:
        openDataServer(double port, double hz, maps* myMaps) ;
        virtual void execute() ;
        void open_thread(int newsockfd) ;

};

// struct for the the thread that receives data from the simulator
// and updates the variables maps

struct read_struct {
    maps* myMaps ;
    int newsockfd ;
    int hz ;

};


#endif //UNTITLED11_OPENDATASERVER_H

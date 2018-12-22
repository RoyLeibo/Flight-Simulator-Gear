
#ifndef UNTITLED11_IO_H
#define UNTITLED11_IO_H

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <netdb.h>
#include <unistd.h>
#include <netinet/in.h>
#include <string.h>
#include <sys/socket.h>
#include <vector>
#include "maps.h"

using namespace std ;


class IO {

public:
    IO() ;
    void read_from_simulator(int newsockfd, maps* myMaps) ;
    vector<double> parser(char* buffer) ;
    void update_map(vector<double> line_vector, maps* myMaps) ;

};


#endif //UNTITLED11_IO_H

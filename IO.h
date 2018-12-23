
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
#include <thread>
#include <chrono>
#include <string>
#include "maps.h"

using namespace std ;


class IO {

public:
    void read_from_simulator(int newsockfd, maps* myMaps, int hz) ;
    void write_to_simulator(int s_num, string s_variable) ;
    vector<double> parser(char* buffer) ;
    void update_map(vector<double> line_vector, maps* myMaps) ;
};


#endif //UNTITLED11_IO_H

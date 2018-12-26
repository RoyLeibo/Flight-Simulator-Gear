
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
    void read_from_simulator(int newsockfd, int hz, maps* myMaps) ;
    void write_to_simulator(string s_variable, double s_value, maps* myMaps) ;
    vector<double> parser(string line) ;
    void update_map(vector<double> line_vector, maps* myMaps) ;
};


#endif //UNTITLED11_IO_H

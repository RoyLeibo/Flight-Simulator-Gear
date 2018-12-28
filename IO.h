
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
#include "Maps.h"

using namespace std ;


class IO {

public:
    void read_from_simulator(int new_sock_fd, int hz, maps* s_maps) ;
    void write_to_simulator(string s_variable, double s_value, maps* s_maps) ;
    vector<double> parser(string line) ;
    void update_map(vector<double> line_vector, maps* s_maps) ;
};


#endif //UNTITLED11_IO_H

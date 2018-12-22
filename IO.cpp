//
// Created by roy on 12/22/18.
//

#include "IO.h"

void IO::read_from_simulator(int newsockfd, maps* myMaps) {
    char buffer[256];
    int n = 0 ;
    while (n >= 0) {
        n = read(newsockfd, buffer, 255);
        if (n < 0) {
            perror("ERROR reading from socket");
            exit(1);
        }
        else {
            update_map(parser(buffer), myMaps) ;
        }
    }
}

vector<double> IO::parser(char* buffer) {
    string line = string(buffer) ;
    int start_index = 0 ;
    int end_index ;
    vector<double> parse_line ;
    line.push_back(',') ;
    for (int i = 0 ; i < 23 ; i++) {
        end_index = line.find(',', start_index) ;
        parse_line.push_back(stod(line.substr(start_index, (end_index - start_index)))) ;
        start_index = end_index + 1 ;
    }
    return parse_line ;
}

void IO::update_map(vector<double> line_vector, maps* myMaps) {
    int counter  = 0 ;
    for(map<string,double>::iterator it = myMaps->begin_it() ; it != myMaps->end_it() ; it++) {
        myMaps->set_double("Read_map", it->first, line_vector.at(counter)) ;
        counter++ ;
    }
}
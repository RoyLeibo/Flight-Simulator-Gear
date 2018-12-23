//
// Created by roy on 12/22/18.
//

#include "IO.h"

void IO::read_from_simulator(char* buffer, int newsockfd, maps* myMaps, int hz) {
    int n = 0 ;
    while (n >= 0) {

        n = read(newsockfd, buffer, 255);
        if (n < 0) {
            perror("ERROR reading from socket");
        }
        else {
            update_map(parser(buffer), myMaps) ;
        }
        std::this_thread::sleep_for((1s)/hz) ;
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
    myMaps->set_double("read_map", "/instrumentation/airspeed-indicator/indicated-speed-kt", line_vector.at(0));
    myMaps->set_double("read_map", "/instrumentation/altimeter/indicated-altitude-ft",line_vector.at(1));
    myMaps->set_double("read_map", "/instrumentation/altimeter/pressure-alt-ft",line_vector.at(2));
    myMaps->set_double("read_map", "/instrumentation/attitude-indicator/indicated-pitch-deg",line_vector.at(3));
    myMaps->set_double("read_map", "/instrumentation/attitude-indicator/indicated-roll-deg",line_vector.at(4));
    myMaps->set_double("read_map", "/instrumentation/attitude-indicator/internal-pitch-deg",line_vector.at(5));
    myMaps->set_double("read_map", "/instrumentation/attitude-indicator/internal-roll-deg",line_vector.at(6));
    myMaps->set_double("read_map", "/instrumentation/encoder/indicated-altitude-ft",line_vector.at(7));
    myMaps->set_double("read_map", "/instrumentation/encoder/pressure-alt-ft",line_vector.at(8));
    myMaps->set_double("read_map", "/instrumentation/gps/indicated-altitude-ft",line_vector.at(9));
    myMaps->set_double("read_map", "/instrumentation/gps/indicated-ground-speed-kt",line_vector.at(10));
    myMaps->set_double("read_map", "/instrumentation/gps/indicated-vertical-speed",line_vector.at(11));
    myMaps->set_double("read_map", "/instrumentation/heading-indicator/indicated-heading-deg",line_vector.at(12));
    myMaps->set_double("read_map", "/instrumentation/magnetic-compass/indicated-heading-deg",line_vector.at(13));
    myMaps->set_double("read_map", "/instrumentation/slip-skid-ball/indicated-slip-skid",line_vector.at(14));
    myMaps->set_double("read_map", "/instrumentation/turn-indicator/indicated-turn-rate",line_vector.at(15));
    myMaps->set_double("read_map", "/instrumentation/vertical-speed-indicator/indicated-speed-fpm",line_vector.at(16));
    myMaps->set_double("read_map", "/controls/flight/aileron",line_vector.at(17));
    myMaps->set_double("read_map", "/controls/flight/elevator",line_vector.at(18));
    myMaps->set_double("read_map", "/controls/flight/rudder",line_vector.at(19));
    myMaps->set_double("read_map", "/controls/flight/flaps",line_vector.at(20));
    myMaps->set_double("read_map", "/controls/engines/engine/throttle",line_vector.at(21));
    myMaps->set_double("read_map", "/engines/engine/rpm",line_vector.at(22));
}

void IO::set_sockfd(int sockfd) {
    this->sockfd = sockfd ;
}
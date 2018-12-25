//
// Created by roy on 12/22/18.
//

#include "IO.h"

/* This function activate after the "OpenDataServer" class is called.
 * The function read 'hz' times per second from the simulator and
 * updates the variables map.
 */

void IO::read_from_simulator(int newsockfd, int hz, maps* myMaps) {
    int n = 0 ;
    char buffer [256] ;
    bzero(buffer,256);
    while (n >= 0) {
        n = read(newsockfd, buffer, 255); // read data from simulator
        if (n < 0) { // if read is fail, print error
            perror("ERROR reading from socket");
        }
        else {
            update_map(parser(buffer), myMaps) ; // calling "update_map" and "parser" functions
        }                                        // to update the variables map
        std::this_thread::sleep_for((1s)/hz) ; // sleep a duration to adjust read hz times per second
    }
}

/* This function write to the simulator.
 * When some variable is binded, after a change has been made
 * this function will write to the simulator the new variable value
 */

void IO::write_to_simulator(double s_num, string s_variable) {
    char buffer[256] ;
    bzero(buffer,256);
    string s = "set " + s_variable + " " + to_string(s_num) + "\r\n" ; // create the command
    for (int i = 0 ; i < s.length() ; i++) { // moving the command into the buffer
        buffer[i] = s[i] ;
    }
    if ((write(g_sockfd, buffer, strlen(buffer)) < 0) { // write to server. if fail, print error
        perror("ERROR writing to socket");
        exit(1);
    }
}

/* This function's argument is a char* of data from the simulator.
 * The function parse all data by ',' symbol and inserts each value
 * into a vector of doubles.
 */

vector<double> IO::parser(char* buffer) {
    string line = string(buffer) ;
    int start_index = 0 ;
    int end_index ;
    vector<double> parse_line ;
    line.push_back(',') ; // pushes another ',' for the last iteration of the loop
    for (int i = 0 ; i < 23 ; i++) {
        end_index = line.find(',', start_index) ; // locate the next ',' sign
        // pushes the sub string from it's start until the ',' symbol
        parse_line.push_back(stod(line.substr(start_index, (end_index - start_index)))) ;
        start_index = end_index + 1 ; // updating the start count after the last ','
    }
    return parse_line ;
}

/* this function's arguments is a vector of doubles which represent all
 * the new variables that has been red from the simulator and a pointer
 * to the "maps" class which contains the map should be updated
 */

void IO::update_map(vector<double> line_vector, maps* myMaps) {
    // update every variable to it's location in the map
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
    myMaps->set_double("read_map", "/controls/engines/current-engine/throttle",line_vector.at(21));
    myMaps->set_double("read_map", "/engines/engine/rpm",line_vector.at(22));
}
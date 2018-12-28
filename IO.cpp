// Created by roy on 12/22/18.
//

#include "IO.h"
#include "command.h"

/* This function activate after the "OpenDataServer" class is called.
 * The function read 'hz' times per second from the simulator and
 * updates the variables map.
 */

void IO::read_from_simulator(int newsockfd, int hz, maps* myMaps) {
    int n = 0, end_of_line = 0, set_counter = 0 ;
    string temp_buffer, remainder = "", result, start_of_string ;
    char buffer [256] ;
    bzero(buffer,256);
    bool is_end_of_line ;
    cout << "I am inside read func" << endl ;
    while (true) {
        if (!myMaps->get_flag()) {
            set_counter++ ;
        }
        cout << "reading..." << endl ;
        memset(buffer, 0, 256) ;
        n = read(newsockfd, buffer, 255); // read data from simulator
        if (n < 0) { // if read is fail, print error
            perror("ERROR reading from socket");
        }
        temp_buffer = buffer ;
        cout << "buffer---------------" << buffer << endl ;
        is_end_of_line = true ;
        result = remainder ;
        while (is_end_of_line) {
            end_of_line = temp_buffer.find('\n', 0) ;
            if (end_of_line > -1) {
                result += temp_buffer.substr(0, end_of_line) ;
                temp_buffer.erase(0, end_of_line+1) ;
                cout<< "sending data to parse and update" << endl ;
                update_map(parser(result), myMaps) ;
                result.clear() ;
                remainder.clear() ;
            }
            else {
                remainder += temp_buffer ;
                is_end_of_line = false ;
            }
        }

//        for (int i = 0 ; i < temp_buffer.length() ; i++) {
//            char c = temp_buffer[i] ;
//            if (temp_buffer[i] == ',') {
//                counter++ ;
//                result.push_back(temp_buffer[i]);
//            }
//            else if (temp_buffer[i] == '\n' && counter == 22) {
//              // int u = 0;
//              // while(u != -1) {
//             //  u = result.find('\000', 0);
//
//              //     if (u != -1) {
//                //       result.erase(u, 1);
//                //   }
//             //  }
//
//                update_map(parser(result), myMaps) ;
//                cout << "result------------ " << result << endl ;
//                result = "" ;
//                counter = 0 ;
//            }
//            else {
//                result.push_back(temp_buffer[i]);
//            }
//        }


//        cout << "buffer: " << temp_buffer << endl;
//        end_of_line = temp_buffer.find('\n') ;
//        if (end_of_line > -1) {
//            end_of_string = temp_buffer.substr(0, end_of_line) ;
//            remainder += end_of_string ;
//            update_map(parser(remainder), myMaps) ;
//            remainder = temp_buffer.substr(end_of_line+1, temp_buffer.length()-end_of_line) ;
//        }
//        else {
//            remainder += temp_buffer ;
//        }
        if (set_counter == 3) {
            myMaps->set_flag(true) ;
            set_counter = 0 ;
        }
    }
}

/* This function write to the simulator.
 * When some variable is binded, after a change has been made
 * this function will write to the simulator the new variable value
 */

void IO::write_to_simulator(string s_variable, double s_value, maps* myMaps) {
    string set ;
    char buffer[256] ;
    bzero(buffer, 256) ;
    set = "set " + s_variable + " " + to_string(s_value) + "\r\n"; // create the command
    for (int i = 0; i < set.length(); i++) { // moving the command into the buffer
        buffer[i] = set[i];
    }
    if (write(myMaps->get_sockfd2(), buffer, strlen(buffer)) < 0) { // write to server. if fail, print error
        perror("ERROR writing to socket");
        exit(1);
    }
    cout <<"finish set " << s_variable << " = " << s_value << endl;
    myMaps->set_flag(false) ;
}

/* This function's argument is a char* of data from the simulator.
 * The function parse all data by ',' symbol and inserts each value
 * into a vector of doubles.
 */

vector<double> IO::parser(string line) {
    int start_index = 0 ;
    int end_index ;
    cout << "data from simulator: " << line << endl ;
    vector<double> parse_line ;
    line.push_back(',') ; // pushes another ',' for the last iteration of the loop
    for (int i = 0 ; i < 23 ; i++) {
        end_index = line.find(',', start_index) ; // locate the next ',' sign
        // pushes the sub string from it's start until the ',' symbol
        cout<<"value number " << i << " is: "<< line.substr(start_index, (end_index - start_index)) << endl ;
        parse_line.push_back(stod(line.substr(start_index, (end_index - start_index)))) ;
        start_index = end_index + 1 ; // updating the start count after the last ','
    }
    cout << "finish parse!" << endl ;
    return parse_line ;
}

/* this function's arguments is a vector of doubles which represent all
 * the new variables that has been red from the simulator and a pointer
 * to the "maps" class which contains the map should be updated
 */

void IO::update_map(vector<double> line_vector, maps* myMaps) {
    cout << "start update" << endl ;
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
    cout << "finish update" << endl ;
}
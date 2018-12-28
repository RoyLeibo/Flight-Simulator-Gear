// Created by roy on 12/22/18.
//

#include "IO.h"
#include "Command.h"

/* This function activate after the "OpenDataServer" class is called.
 * The function read 'hz' times per second from the simulator and
 * updates the variables map.
 */

void IO::read_from_simulator(int new_sock_fd, int hz, maps* s_maps) {
    int n = 0, end_of_line = 0, set_counter = 0 ;
    string temp_buffer, remainder = "", result, start_of_string ;
    char buffer [256] ;
    bzero(buffer,256);
    bool is_end_of_line ;
    cout << "I am inside read func" << endl ;
    while (true) {
        if (!s_maps->get_flag()) { // if a set committed, the data has to update first in the map
            set_counter++ ; // count the number of loop run when flag is false
        }
        cout << "reading..." << endl ;
        memset(buffer, 0, 256) ; // set buffer to 0
        n = read(new_sock_fd, buffer, 255); // read data from simulator
        if (n < 0) { // if read is fail, print error
            perror("ERROR reading from socket");
        }
        temp_buffer = buffer ;
        cout << "buffer---------------" << buffer << endl ;
        is_end_of_line = true ;
        result = remainder ; // adding the remainder data from last read
        while (is_end_of_line) {
            end_of_line = temp_buffer.find('\n', 0) ; // finding \n sybol
            if (end_of_line > -1) { // if \n found
                result += temp_buffer.substr(0, end_of_line) ; // adding to result the sub string
                temp_buffer.erase(0, end_of_line+1) ; // erasing the data added to result
                cout<< "sending data to parse and update" << endl ;
                update_map(parser(result), s_maps) ; // updating the data map with the new data received
                result.clear() ; // clear result string
                remainder.clear() ; // clear remainder string
            }
            else { // if \n not found
                remainder += temp_buffer ; // save the not full data variables received from simulator
                is_end_of_line = false ; // exit while loop
            }
        }
        if (set_counter == 3) { // after 3 loops, the new data has certainly updated
            s_maps->set_flag(true) ; // release the main thread
            set_counter = 0 ;
        }
    }
}

/* This function write to the simulator.
 * When some variable is binded, after a change has been made
 * this function will write to the simulator the new variable value
 */

void IO::write_to_simulator(string s_variable, double s_value, maps* s_maps) {
    string set ;
    char buffer[256] ;
    bzero(buffer, 256) ;
    set = "set " + s_variable + " " + to_string(s_value) + "\r\n"; // create the Command
    for (int i = 0; i < set.length(); i++) { // moving the Command into the buffer
        buffer[i] = set[i];
    }
    if (write(s_maps->get_sockfd2(), buffer, strlen(buffer)) < 0) { // write to server. if fail, print error
        perror("ERROR writing to socket");
        exit(1);
    }
    cout <<"finish set " << s_variable << " = " << s_value << endl;
    s_maps->set_flag(false) ; // after write to server, the main thread cannot continue until the new
}                             //  data has been updated in the map

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

void IO::update_map(vector<double> line_vector, maps* s_maps) {
    cout << "start update" << endl ;
    // update every variable to it's location in the map
    s_maps->set_double("read_map", "/instrumentation/airspeed-indicator/indicated-speed-kt", line_vector.at(0));
    s_maps->set_double("read_map", "/instrumentation/altimeter/indicated-altitude-ft",line_vector.at(1));
    s_maps->set_double("read_map", "/instrumentation/altimeter/pressure-alt-ft",line_vector.at(2));
    s_maps->set_double("read_map", "/instrumentation/attitude-indicator/indicated-pitch-deg",line_vector.at(3));
    s_maps->set_double("read_map", "/instrumentation/attitude-indicator/indicated-roll-deg",line_vector.at(4));
    s_maps->set_double("read_map", "/instrumentation/attitude-indicator/internal-pitch-deg",line_vector.at(5));
    s_maps->set_double("read_map", "/instrumentation/attitude-indicator/internal-roll-deg",line_vector.at(6));
    s_maps->set_double("read_map", "/instrumentation/encoder/indicated-altitude-ft",line_vector.at(7));
    s_maps->set_double("read_map", "/instrumentation/encoder/pressure-alt-ft",line_vector.at(8));
    s_maps->set_double("read_map", "/instrumentation/gps/indicated-altitude-ft",line_vector.at(9));
    s_maps->set_double("read_map", "/instrumentation/gps/indicated-ground-speed-kt",line_vector.at(10));
    s_maps->set_double("read_map", "/instrumentation/gps/indicated-vertical-speed",line_vector.at(11));
    s_maps->set_double("read_map", "/instrumentation/heading-indicator/indicated-heading-deg",line_vector.at(12));
    s_maps->set_double("read_map", "/instrumentation/magnetic-compass/indicated-heading-deg",line_vector.at(13));
    s_maps->set_double("read_map", "/instrumentation/slip-skid-ball/indicated-slip-skid",line_vector.at(14));
    s_maps->set_double("read_map", "/instrumentation/turn-indicator/indicated-turn-rate",line_vector.at(15));
    s_maps->set_double("read_map", "/instrumentation/vertical-speed-indicator/indicated-speed-fpm",line_vector.at(16));
    s_maps->set_double("read_map", "/controls/flight/aileron",line_vector.at(17));
    s_maps->set_double("read_map", "/controls/flight/elevator",line_vector.at(18));
    s_maps->set_double("read_map", "/controls/flight/rudder",line_vector.at(19));
    s_maps->set_double("read_map", "/controls/flight/flaps",line_vector.at(20));
    s_maps->set_double("read_map", "/controls/engines/current-engine/throttle",line_vector.at(21));
    s_maps->set_double("read_map", "/engines/engine/rpm",line_vector.at(22));
    cout << "finish update" << endl ;
}
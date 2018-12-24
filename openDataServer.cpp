//
// Created by roy on 12/17/18.
//

#include "openDataServer.h"

// Function that is operates in the thread which receives data from simulator.
// The function calls "read_from_simulator" function which reads the data is
// sent from the simulator

void* run_read_from_simulator(void* arg) {
    struct read_struct* arg_struct = (read_struct*)arg ;
    arg_struct->read_from_simulator() ;
}

openDataServer::openDataServer(double port, double hz, maps* myMaps) {
    if (port > 0) { // INPUT CHECK NEEDED
        this->port = port;
    }
    if (hz > 0) {
        this->hz = hz;
    }
    this->myMaps = myMaps ;
}

void openDataServer::execute() {
    int sockfd, newsockfd, clilen;
    struct sockaddr_in serv_addr, cli_addr;
    IO io ;

    sockfd = socket(AF_INET, SOCK_STREAM, 0); // calling to socket function

    if (sockfd < 0) { // if the function failed, print error
        perror("cannot open socket, please try again");
        exit(1);
    }

    bzero((char *) &serv_addr, sizeof(serv_addr)); // initialize the socket struct

    // update socket's data
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port = htons(this->port);

    if (bind(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0) { // binding host address
        perror("cannot bind to server");
        exit(1);
    }

    listen(sockfd,1); // wait for a connection request
    clilen = sizeof(cli_addr);

    // accept the connection request
    newsockfd = accept(sockfd, (struct sockaddr *)&cli_addr, (socklen_t*)&clilen);

    if (newsockfd < 0) { // if connection failed, print error
        perror("cannot accept your connection request");
        exit(1);
    }
    open_thread(newsockfd) ;
}

// initialize the thread struct and create a new thread

void openDataServer::open_thread(int newsockfd) {

    // after connection has established, initialize a thread for reading data from the simulator
    pthread_t tid ;
    pthread_attr_t attr ;
    pthread_attr_init(&attr) ;

    // initialize struct
    struct read_struct r_s ;
    r_s.newsockfd = newsockfd ;
    r_s.myMaps = myMaps ;
    r_s.hz = hz ;

    // create a thread with the struct and a function which reads data from the simulator,
    // parse it and update the variables map
    pthread_create(&tid, &attr, run_read_from_simulator, &r_s) ;
}

/* This function activate after the "OpenDataServer" class is called.
 * The function read 'hz' times per second from the simulator and
 * updates the variables map.
 */

void read_struct::read_from_simulator() {
    int n = 0 ;
    char buffer [256] ;
    bzero(buffer,256);
    while (n >= 0) {

        n = read(this->sockfd, buffer, 255); // read data from simulator
        if (n < 0) { // if read is fail, print error
            perror("ERROR reading from socket");
        }
        else {
            update_map(parser(buffer), this->myMaps) ; // calling "update_map" and "parser" functions
        }                                        // to update the variables map
        std::this_thread::sleep_for((1s)/this->hz) ; // sleep a duration to adjust read hz times per second
    }
}

/* This function's argument is a char* of data from the simulator.
 * The function parse all data by ',' symbol and inserts each value
 * into a vector of doubles.
 */

vector<double> read_struct::parser(char* buffer) {
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

void read_struct::update_map(vector<double> line_vector, maps* myMaps) {
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
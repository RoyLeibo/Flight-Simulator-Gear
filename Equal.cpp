//
// Created by einat on 12/21/18.
//

#include "Equal.h"

// two questions: did we handle cases when some variable should be equal to other variable?
// diffrence in the use of set_double for "symbole_table" and for insert_double

Equal::Equal(string variable, double num, maps* map)
{
    s_variable = variable;
    s_num = num;
    s_map = map;
}
void Equal::execute()
{

    // need to check if it should be read_map or path_map

    bool is_in_map = s_map->is_value_in_map("symbols_tables", s_variable);
    if(is_in_map)
    {
        s_map->set_double("symbols_tables", s_variable, s_num);
    }
    is_in_map = s_map->is_value_in_map("read_map", s_variable);
    if (is_in_map)
    {
       write_to_simulator(s_num, s_variable) ;
    }
    else {
        s_map->insert_double("read_map", s_variable, s_num) ;
        write_to_simulator(s_num, s_variable) ;
    }
}

/* This function write to the simulator.
 * When some variable is binded, after a change has been made
 * this function will write to the simulator the new variable value
 */

void Equal::write_to_simulator(double s_num, string s_variable) {
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

//
// Created by einat on 12/17/18.
//

#ifndef PORCJECT_MAP_H
#define PORCJECT_MAP_H

#include <map>
#include <string>
#include <iterator>

enum Maps {Map_command, Symbols_table, Map_path, Operator_Priority_map, Read_map, Map_operators};
using namespace std;

/* This class is a maps class, which include all operates needed for all the
 * maps that is used during the program.
 * This map is created only once, and a pointer to it's new object is transported throuht
 * the entire program.
 */

class maps {
    private:
        map<string,int> s_map_command; // map of all commands
        map<string,double > s_symbol_table; // map for variables that is not binded
        map<string,Maps> s_map_map; // map of all maps
        map<string,string> s_map_path; // map of variables and their path
        map<char,int> s_map_operator_priority ; // map for operator priorities
        map<string,double> s_map_read; // map for all data is binded to the simulator
        map<string,int>s_map_operators; // operator map
        bool flag ; // flag that indicates if it is possible to get data from map.
                    // the flag is true only when the data is the most updated data from
                    // from the simulator
        int sockfd1 ; // server socket
        int sockfd2 ; // client socket

    public:
        maps();
        void insert_double(string table, string key, double value) ;
        void set_double(string table, string key, double value) ;
        void set_double(string key,double value);
        void set_string(string table,string key, string path);
        int get_int(string table,string key);
        int get_int(string table,char key);
        double get_double(string key);
        string get_string(string table,string key);
        map<string,Maps>create_map_map();
        map<string, int>create_map_command();
        map<char,int> create_map_operator_priority();
        map<string,int> create_map_operators();
        map<string,double> create_map_read() ;
        bool is_value_in_map(string table, string value);
        void deletd_value(string key);
        int get_sockfd1() ;
        int get_sockfd2() ;
        bool get_flag() ;
        void set_flag(bool flag) ;
        void set_sockfd1(int sockfd1) ;
        void set_sockfd2(int sockfd2) ;
};


#endif //PORCJECT_MAP_H

//
// Created by einat on 12/17/18.
//

#include "Maps.h"
#include <string>
#include <iterator>
#include "IO.h"
using namespace std;

maps::maps()
{
    s_map_command = create_map_command();
    s_map_map = create_map_map();
    s_map_operator_priority = create_map_operator_priority();
    s_map_read = create_map_read();
    s_map_operators = create_map_operators();
    this->flag = true ;

}

//get map name,key and value
//insert the value in the map in the right place

void maps::insert_double(string table, string key, double value) {
    Maps current_table = s_map_map[table];
    switch (current_table)
    {
        case Symbols_table:
            s_symbol_table.insert(pair<string,double>(key,value));
            break ;
        case Read_map:
            s_map_read.insert(pair<string,double>(key,value));
    }
}

void maps::set_double(string table, string key, double value) {
    Maps current_table = s_map_map[table];
    switch (current_table)
    {
        case Read_map:
            s_map_read[key] = value;
    }
}

/* This function gets a key and a value to update this key,
 * The function searches in the 2 maps that there is values in,
 * and checks if the variable is binded to some other variable.
 */

void maps::set_double(string key, double value)
{
    bool flag = true ; // flag for loop
    while(flag) {
        if (is_value_in_map("symbols_tables", key)) { // check if the key is in the symbole_table map
            s_symbol_table[key] = value; // updated value
            flag = false ; // exit loop
        }
        else if (is_value_in_map("read_map", get_string("map_path", key))) { // check if the key is in the map_read
            IO().write_to_simulator(get_string("map_path", key), value, this); // write to simulator the data
            flag = false ; // exit loop
        }
        else { // check if the key is binded to another variable
            if (is_value_in_map("symbols_tables", s_map_path[key])) { // check in symbols_tables map
                s_symbol_table[s_map_path[key]] = value; // update data
                flag = false ; // exit loop
            }
            else if (is_value_in_map("read_map", get_string("map_path", s_map_path[key]))) { // check in map_read
                IO().write_to_simulator(get_string("map_path", key), value, this); // update data
                flag = false ; // exit loop
            }
        }
        if (flag) {
            key = s_map_path[key];
        }
    }
}

/* This function gets a variables, value and a map to update.
 * The functions sets the new value of the variables in the specific map
 */
void maps::set_string(string table,string key, string path)
{
    Maps current_table = s_map_map[table];
    switch (current_table)
    {
        case Map_path:
            s_map_path.insert(pair<string,string>(key,path));
            if(!is_value_in_map("read_map", path)) {
                insert_double("read_map", path, 0.0) ;
            }
    }
}

//get name map and string key
//return the value in this key

int maps::get_int(string table,string key)
{
    Maps current_table = s_map_map[table];
    switch(current_table)
    {
        case Map_command:
            return s_map_command[key];
        case Map_operators:
            return s_map_operators[key];
    }
    return 1 ;
}

//get name map and char key
//return the value in this key

int maps::get_int(string table,char key) {
    Maps current_table = s_map_map[table];
    switch(current_table)
    {
        case Operator_Priority_map:
            return s_map_operator_priority[key];
        /*case Map_operators:
            return s_map_operators[key];*/
    }
    return 1;
}

/* This function gets a key and returns the double value of that key.
 * if the value is in the map_read map, the function check the confirmation of
 * updated data flag.
 * If data access denied (flag is false) the function stops (endless while loop)
 * until the flag has been updated to true.
 * The function also checks if the variable is binded to another variable.
 */

double maps::get_double(string key)
{
    int i = 0 ;
    while(true) {
        if (is_value_in_map("symbols_tables", key)) { // check if the key is in the symbole_table map
            return s_symbol_table[key]; //return double value
        }
        else if (is_value_in_map("read_map", key)) { // check if the key is in the map_read
            cout<< key << "====== before update: " <<  s_map_read[key] << "\n" ;
            while (!(this->flag)) {} // if flag is false, wait until it is true
            cout<< key << "====== after update: " <<  s_map_read[key] << "\n" ;
            return s_map_read[key]; //return double value
        }
        else {
            if (is_value_in_map("symbols_tables", s_map_path[key])) { // check if in the symbole_table map
                return s_symbol_table[s_map_path[key]]; //return double value
            }
            else if (is_value_in_map("read_map", s_map_path[key])) { // check if in the map_read
                cout<< key << "====== before update: " <<  s_map_read[s_map_path[key]] << "\n" ;
                while (!(this->flag)) {} // if flag is false, wait until it is true
                cout<< key << "====== after update: " <<  s_map_read[s_map_path[key]] << "\n" ;
                return s_map_read[s_map_path[key]]; //return double value
            }
        }
        key = s_map_path[key] ;
    }
}

// returns a string in the table

string maps::get_string(string table,string key)
{
    Maps current_table = s_map_map[table];
    switch(current_table)
    {
        case Map_path:
            return s_map_path[key];
    }
    return "" ;
}

//crate map of maps

map<string,Maps> maps::create_map_map()
{
    map<string,Maps > map_map;
    map_map.insert(pair<string,Maps>("map_command",Map_command));
    map_map.insert(pair<string,Maps>("symbols_tables",Symbols_table));
    map_map.insert(pair<string,Maps>("map_path",Map_path));
    map_map.insert(pair<string,Maps>("operator_priority_map",Operator_Priority_map));
    map_map.insert(pair<string,Maps>("read_map",Read_map));
    map_map.insert(pair<string,Maps>("map_operators",Map_operators));
    return map_map;

}

//crate map of Command

map<string, int> maps::create_map_command()
{
    map <string,int> map_command;
    map_command.insert(pair<string,int>("openDataServer",1));
    map_command.insert(pair<string,int>("connect",2));
    map_command.insert(pair<string,int>("var",3));
    map_command.insert(pair<string,int>("=",4));
    map_command.insert(pair<string,int>("print",5));
    map_command.insert(pair<string,int>("sleep",6));
    map_command.insert(pair<string,int>("while",7));
    map_command.insert(pair<string,int>("if",8));
    map_command.insert(pair<string,int>("Enterc",9));
    return map_command;
}

// create an operator priority map

map<char, int> maps::create_map_operator_priority() {
    map <char, int> map_operator_priority ;
    map_operator_priority.insert(pair<char,int>('+',1));
    map_operator_priority.insert(pair<char,int>('-',1));
    map_operator_priority.insert(pair<char,int>('*',2));
    map_operator_priority.insert(pair<char,int>('/',2));
    map_operator_priority.insert(pair<char,int>('(',3));
    map_operator_priority.insert(pair<char,int>(')',4));
    return map_operator_priority ;
}

// create a map_read map

map<string,double> maps::create_map_read()
{
    map<string,double > map_read ;
    map_read.insert(pair<string,double>("/instrumentation/airspeed-indicator/indicated-speed-kt",0));
    map_read.insert(pair<string,double>("/instrumentation/altimeter/indicated-altitude-ft",0));
    map_read.insert(pair<string,double>("/instrumentation/altimeter/pressure-alt-ft",0));
    map_read.insert(pair<string,double>("/instrumentation/attitude-indicator/indicated-pitch-deg",0));
    map_read.insert(pair<string,double>("/instrumentation/attitude-indicator/indicated-roll-deg",0));
    map_read.insert(pair<string,double>("/instrumentation/attitude-indicator/internal-pitch-deg",0));
    map_read.insert(pair<string,double>("/instrumentation/attitude-indicator/internal-roll-deg",0));
    map_read.insert(pair<string,double>("/instrumentation/encoder/indicated-altitude-ft",0));
    map_read.insert(pair<string,double>("/instrumentation/encoder/pressure-alt-ft",0));
    map_read.insert(pair<string,double>("/instrumentation/gps/indicated-altitude-ft",0));
    map_read.insert(pair<string,double>("/instrumentation/gps/indicated-ground-speed-kt",0));
    map_read.insert(pair<string,double>("/instrumentation/gps/indicated-vertical-speed",0));
    map_read.insert(pair<string,double>("/instrumentation/heading-indicator/indicated-heading-deg",0));
    map_read.insert(pair<string,double>("/instrumentation/magnetic-compass/indicated-heading-deg",0));
    map_read.insert(pair<string,double>("/instrumentation/slip-skid-ball/indicated-slip-skid",0));
    map_read.insert(pair<string,double>("/instrumentation/turn-indicator/indicated-turn-rate",0));
    map_read.insert(pair<string,double>("/instrumentation/vertical-speed-indicator/indicated-speed-fpm",0));
    map_read.insert(pair<string,double>("/controls/flight/aileron",0));
    map_read.insert(pair<string,double>("/controls/flight/elevator",0));
    map_read.insert(pair<string,double>("/controls/flight/rudder",0));
    map_read.insert(pair<string,double>("/controls/flight/flaps",0));
    map_read.insert(pair<string,double>("/controls/engines/current-engine/throttle",0));
    map_read.insert(pair<string,double>("/engines/engine/rpm",0));

    return map_read ;
}

//get table name and value
//return if the value is in the map

bool maps::is_value_in_map(string table, string value)
{
    Maps current_table = s_map_map[table];
    map<string,int>::iterator it;
    map<string,double>::iterator id;
    map<string,string>::iterator is;
    map<char,int>::iterator in;
    switch(current_table)
    {
        case Map_command:
            it = s_map_command.find(value);
            if(it == s_map_command.end())
            {
                return false;
            }
            else
            {
                return true;
            }
        case Symbols_table:
            id = s_symbol_table.find(value);
            if(id == s_symbol_table.end())
            {
                return false;
            }
            else
            {
                return true;
            }
        case Map_path:
            is = s_map_path.find(value);
            if(is == s_map_path.end())
            {
                return false;
            }
            else
            {
                return true;
            }
        case Operator_Priority_map:
            in = s_map_operator_priority.find(value[0]);
            if(in == s_map_operator_priority.end())
            {
                return false;
            }
            else
            {
                return true;
            }

        case Read_map:
            id = s_map_read.find(value);
            if(id == s_map_read.end())
            {
                return false;
            }
            else
            {
                return true;
            }
    }
    return false ;
}

// delete value from map

void maps::deletd_value(string key)
{
    map<string,double>::iterator id;
    id = s_symbol_table.find(key);
    s_symbol_table.erase(id);
}

// creates an operators map

map<string,int> maps:: create_map_operators()
{
    map<string,int> res;
    res.insert(pair<string,int>("<",1));
    res.insert(pair<string,int>(">",2));
    res.insert(pair<string,int>("==",3));
    res.insert(pair<string,int>("!=",4));
    res.insert(pair<string,int>(">=",5));
    res.insert(pair<string,int>("<=",6));
    return res;
}

int maps::get_sockfd1() {
    return this->sockfd1 ;
}

int maps::get_sockfd2() {
    return this->sockfd2 ;
}

bool maps::get_flag() {
    return this->flag ;
}

void maps::set_flag(bool flag) {
    this->flag = flag ;
}

void maps::set_sockfd1(int sockfd1) {
    this->sockfd1 = sockfd1 ;
};

void maps::set_sockfd2(int sockfd2) {
    this->sockfd2 = sockfd2 ;
};

maps::~maps() {}
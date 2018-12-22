//
// Created by einat on 12/17/18.
//

#include "maps.h"
#include <string>
#include <iterator>
using namespace std;

maps::maps()
{
    s_map_command = create_map_command();
    s_map_map = create_map_map();
    s_map_operator_priority = create_map_operator_priority();
    s_map_read = create_map_read();
    s_map_operators = create_map_operators();

}

//*****check if it only to symbols tables if yes no need of switch case****
//get map name,key and value
//insert the value in the map in the right place
void maps::set_double(string table,string key,double value)
{
    Maps current_table = s_map_map[table];
    switch (current_table)
    {
        case Symbols_table:
            s_symbole_tables.insert(pair<string,double>(key,value));

        case Read_map:
            s_map_read[key] = value ;
    }
}
void maps::set_string(string table,string key, string path)
{
    Maps current_table = s_map_map[table];
    switch (current_table)
    {
        case Map_path:
            s_map_path.insert(pair<string,string>(key,path));
    }
}

//get name table and key
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
}

int maps::get_int(string table,char key) {
    Maps current_table = s_map_map[table];
    switch(current_table)
    {
        case Operator_Priority_map:
            return s_map_operator_priority[key];
        case Map_operators:
            return s_map_operators[key];
    }
}

double maps::get_double(string table, string key)
{
    Maps current_table = s_map_map[table];
    switch(current_table)
    {
        case Symbols_table:
            return s_symbole_tables[key];

        case Read_map:
            return s_map_read[key] ;
    }
}

string maps::get_string(string table,string key)
{
    Maps current_table = s_map_map[table];
    switch(current_table)
    {
        case Map_path:
            return s_map_path[key];
    }
}

//crate map of maps ****to check if there is way to return refrens if map***
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

//crate map of command ****to check if there is way to return refrens if map***
map<string, int> maps::create_map_command()
{
    map <string,int> map_commend;
    map_commend.insert(pair<string,int>("openDataServer",1));
    map_commend.insert(pair<string,int>("connect",2));
    map_commend.insert(pair<string,int>("var",3));
    map_commend.insert(pair<string,int>("=",4));
    map_commend.insert(pair<string,int>("print",5));
    map_commend.insert(pair<string,int>("sleep",6));
    map_commend.insert(pair<string,int>("while",7));
    map_commend.insert(pair<string,int>("if",8));
    return map_commend;
}

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
    map_read.insert(pair<string,double>("/controls/engines/engine/throttle",0));
    map_read.insert(pair<string,double>("/engines/engine/rpm",0));
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
            id = s_symbole_tables.find(value);
            if(id == s_symbole_tables.end())
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

    }
}

map<string,double>::iterator maps::begin_it() {
    return s_map_read.begin() ;
}

map<string,double>::iterator maps::end_it() {
    return s_map_read.end() ;
}

void maps::deletd_value(string key)
{
    map<string,double>::iterator id;
    id = s_symbole_tables.find(key);
    s_symbole_tables.erase(id);
}

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
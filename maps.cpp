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
    }
}

int maps::get_int(string table,char key) {
    Maps current_table = s_map_map[table];
    switch(current_table)
    {
        case Operator_Priority_map:
            return s_map_operator_priority[key];
    }
}

double maps::get_double(string table, string key)
{
    Maps current_table = s_map_map[table];
    switch(current_table)
    {
        case Symbols_table:
            return s_symbole_tables[key];
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
    return map_map;

}
// comment

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
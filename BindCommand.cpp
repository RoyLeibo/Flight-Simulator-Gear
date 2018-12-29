//
// Created by einat on 12/21/18.
//

#include "BindCommand.h"

BindCommand::BindCommand(string key, string path, maps* map)
{
    this->s_key = key;
    this->s_path = delete_quotation_marks(path) ;
    this->s_maps = map;
}

//insert the ke and path to map_path
void BindCommand::execute()
{
    s_maps->set_string("map_path", s_key, s_path);
}

//function that get the path and return string with out quotation marks
string BindCommand::delete_quotation_marks(string s_path) {
    if (s_path[0] != '"') {
        return s_path ;
    }
    else {
        s_path.erase(0, 1) ;
        s_path.erase(s_path.length()-1, 1) ;
        return s_path ;
    }
}
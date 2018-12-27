//
// Created by einat on 12/21/18.
//

#include "BindCommand.h"

BindCommand::BindCommand(string key, string path, maps* map)
{
    this->s_key = key;
    this->s_path = delete_quotation_marks(path) ;
    this->s_map = map;
}
void BindCommand::execute()
{
 //   s_map->deletd_value(s_key);
    s_map->set_string("map_path", s_key, s_path);
}

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
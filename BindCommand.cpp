//
// Created by einat on 12/21/18.
//

#include "BindCommand.h"

BindCommand::BindCommand(string key, string path, maps* map)
{
    s_key = key;
    s_path = path;
    s_map = map;
}
void BindCommand::execute()
{
 //   s_map->deletd_value(s_key);
    s_map->insert_string("map_path", s_key, s_path);
}
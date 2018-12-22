//
// Created by einat on 12/21/18.
//

#include "bind.h"

bind::bind(string key, string path, maps* map)
{
    s_key = key;
    s_path = path;
    s_map = map;
}
void bind::execute()
{
    s_map->deletd_value(s_key);
    s_map->set_string("map_path", s_key, s_path);
}
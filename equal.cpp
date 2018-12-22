//
// Created by einat on 12/21/18.
//

#include "equal.h"

equal::equal(string variable, double num, maps* map)
{
    s_variable = variable;
    s_num = num;
    s_map = map;
}
void equal:: execute()
{
    bool is_in_map = s_map->is_value_in_map("symbols_tables", s_variable);
    if(is_in_map)
    {
        s_map->set_double("symbols_tables", s_variable, s_num);
    }
    else
    {
        s_map->set_double("read_map", s_variable);
    }
}

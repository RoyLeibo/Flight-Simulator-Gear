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
        IO().write_to_simulator(s_variable, s_num, s_map) ;
    }
}

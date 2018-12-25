//
// Created by einat on 12/21/18.
//

#include "Ifcommand.h"
#include "controler.h"
#include "dijkstra.h"

Ifcommand::Ifcommand(vector<vector<string>> vec, maps* map)
{
    s_vec = vec;
    s_map = map;
}
void Ifcommand:: execute()
{
    double variable_one = 0;
    double variable_two = 0;
    if (s_map->is_value_in_map("symbols_tables", s_vec[0][1]))
    {
        variable_one = s_map->get_double("symbols_tables", s_vec[0][1]);
    }
    else if (s_map->is_value_in_map("read_map", s_vec[0][1]))
    {
        variable_one = s_map->get_double("read_map", s_vec[0][1]);
    }
    else
    {
        variable_one = dijkstra().calc(s_vec[0][1],s_map);
    }
    if (s_map->is_value_in_map("symbols_tables", s_vec[0][3]))
    {
        variable_two = s_map->get_double("symbols_tables", s_vec[0][3]);
    }
    else if (s_map->is_value_in_map("read_map", s_vec[0][3]))
    {
        variable_two = s_map->get_double("read_map", s_vec[0][3]);
    }
    else
    {
        variable_two = dijkstra().calc(s_vec[0][3],s_map);
    }
    switch (s_map->get_int("map_operators", s_vec[0][2]))
    {
        case 1:
            if (variable_one < variable_two)
            {
                do_if();
            }
            break;
        case 2:
            if (variable_one > variable_two)
            {
                do_if();
            }
            break;
        case 3:
            if (variable_one == variable_two)
            {
                do_if();
            }
            break;
        case 4:
            if (variable_one != variable_two) {
                do_if();
            }
            break;
        case 5:
            if (variable_one >= variable_two) {
                do_if();
            }
            break;
        case 6:
            if (variable_one <= variable_two)
            {
                do_if();
            }
            break;
    }
}

void Ifcommand::do_if()
{
    int index = 1;
    while(index <s_vec.size())
    {
        controler(s_map).parsar(s_vec.at(index));
    }
}
//
// Created by einat on 12/21/18.
//

#include "Ifcommand.h"
#include "Controler.h"
#include "Dijkstra.h"

Ifcommand::Ifcommand(vector<vector<string>> vec, maps* map)
{
    s_vec = vec;
    s_maps = map;
}
void Ifcommand:: execute()
{
    double variable_one = 0;
    double variable_two = 0;
    //if the value is in symbols tables
    if (s_maps->is_value_in_map("symbols_tables", s_vec[0][1]))
    {
        variable_one = s_maps->get_double(s_vec[0][1]);
    }
    //if the value in map read
    else if (s_maps->is_value_in_map("map_path", s_vec[0][1]))
    {
        variable_one = s_maps->get_double(s_vec[0][1]);
    }
    else
    {
        variable_one = dijkstra().calc(s_vec[0][1],s_maps);
    }
    //second value
    if (s_maps->is_value_in_map("symbols_tables", s_vec[0][3]))
    {
        variable_two = s_maps->get_double(s_vec[0][3]);
    }
    else if (s_maps->is_value_in_map("map_path", s_vec[0][3]))
    {
        variable_two = s_maps->get_double(s_vec[0][3]);
    }
    else
    {
        variable_two = dijkstra().calc(s_vec[0][3],s_maps);
    }
    switch (s_maps->get_int("map_operators", s_vec[0][2]))
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
        controler(s_maps).parsar(s_vec.at(index));
        index++;
    }
}
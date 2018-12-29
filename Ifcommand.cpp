//
// Created by einat on 12/21/18.
//

#include "Ifcommand.h"
#include "Controler.h"
#include "Dijkstra.h"
#define  ZERO 0
#define ONE 1
#define  TWO 2
#define  THREE 3

Ifcommand::Ifcommand(vector<vector<string>> vec, maps* map)
{
    s_vec = vec;
    s_maps = map;
}
void Ifcommand:: execute()
{
    double variable_one = 0;
    double variable_two = 0;
    string first_variable = s_vec[ZERO][ONE];
    string second_variable = s_vec[ZERO][THREE];
    //check what is the value of the of the first variable in the condition of the while loop
    //if the value is in symbols tables
    if (s_maps->is_value_in_map("symbols_tables",first_variable))
    {
        variable_one = s_maps->get_double(first_variable);
    }
    //if the value in map read
    else if (s_maps->is_value_in_map("map_path",first_variable))
    {
        variable_one = s_maps->get_double(first_variable);
    }
    //if it expression or number
    else
    {
        variable_one = dijkstra().calc(s_vec[0][1],s_maps);
    }
    //check what is the value of the of the second variable in the condition of the while loop
    //if the value is in symbols tables
    if (s_maps->is_value_in_map("symbols_tables", second_variable))
    {
        variable_two = s_maps->get_double(second_variable);
    }
    //if the value in map read
    else if (s_maps->is_value_in_map("map_path", second_variable))
    {
        variable_two = s_maps->get_double(second_variable);
    }
    //if it expression or number
    else
    {
        variable_two = dijkstra().calc(second_variable,s_maps);
    }
    /*check what is the operator and go to the right case
     *if the condition met do all the command in the if condition
     */
    switch (s_maps->get_int("map_operators", s_vec[ZERO][TWO]))
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

//function that activates all the commend in the if condition
void Ifcommand::do_if()
{
    int index = ONE;
    while(index <s_vec.size())
    {
        controler(s_maps).parsar(s_vec.at(index));
        index++;
    }
}
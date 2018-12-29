//
// Created by einat on 12/21/18.
//

#include "Whilecommand.h"
#include "Controler.h"
#include "Dijkstra.h"
#define  ZERO 0
#define ONE 1
#define  TWO 2
#define  THREE 3

Whilecommand::Whilecommand(vector<vector<string>> vec, maps* map)
{
    s_vec = vec;
    s_maps = map;
}

//use data member s_vec add while loop
void Whilecommand:: execute()
{
    double variable_one = 0;
    double variable_two = 0;
    string first_variable;
    string second_variable;
    bool flg = true;
    while (flg) {
         variable_one = 0;
         variable_two = 0;
        first_variable = s_vec[ZERO][ONE];
        second_variable = s_vec[ZERO][THREE];
        //check what is the value of the of the first variable in the condition of the while loop
        //if the value is in symbols tables
        if (s_maps->is_value_in_map("symbols_tables", first_variable))
        {
            variable_one = s_maps->get_double(first_variable);
        }
        //if the value in map read
        else if (s_maps->is_value_in_map("map_path", first_variable))
        {
            variable_one = s_maps->get_double(first_variable);
        }
        //if it expression or number
        else
        {
            variable_one = dijkstra().calc(first_variable, s_maps);
        }
        //check what is the value of the of the second variable in the condition of the while loop
        if (s_maps->is_value_in_map("symbols_tables", second_variable))
        {
            variable_two = s_maps->get_double(second_variable);
        }
        else if (s_maps->is_value_in_map("map_path",second_variable))
        {
            variable_two = s_maps->get_double(second_variable);
        }
        else
        {
            variable_two = dijkstra().calc(second_variable, s_maps);
        }
        /*check what is the operator and go to the right case
         *if the condition met do the while loop if not chang the flg and exit
         */
        switch (s_maps->get_int("map_operators", s_vec[ZERO][TWO])) {
            case 1:
                if (variable_one < variable_two) {
                    do_while();

                }
                else
                {
                    flg = false;
                }
                break;
            case 2:
                if (variable_one > variable_two)
                {
                    do_while();
                }
                else
                {
                    flg = false;
                }
                break;
            case 3:
                if (variable_one == variable_two)
                {
                    do_while();

                }
                else
                {
                    flg = false;
                }
                break;
            case 4:
                if (variable_one != variable_two)
                {
                    do_while();

                }
                else
                {
                    flg = false;
                }
                break;
            case 5:
                if (variable_one >= variable_two)
                {
                    do_while();
                }
                else
                {
                    flg = false;
                }
                break;
            case 6:
                if (variable_one <= variable_two)
                {
                    do_while();
                }
                else
                {
                    flg = false;
                }
                break;
        }
    }
}

//function that activates all the commend in the loop
void Whilecommand::do_while()
{
    int index = ONE;
    while(index <s_vec.size())
    {
        controler(s_maps).parsar(s_vec.at(index));
        index++;
    }
}
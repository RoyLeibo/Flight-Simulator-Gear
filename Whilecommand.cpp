//
// Created by einat on 12/21/18.
//

#include "Whilecommand.h"
#include "Controler.h"

Whilecommand::Whilecommand(vector<vector<string>> vec, maps* map)
{
    s_vec = vec;
    s_maps = map;
}
void Whilecommand:: execute()
{
    bool flg = true;
    while (flg) {
        double variable_one = 0;
        double variable_two = 0;
        if (s_maps->is_value_in_map("symbols_tables", s_vec[0][1]))
        {
            variable_one = s_maps->get_double(s_vec[0][1]);
        }
        else if (s_maps->is_value_in_map("map_path", s_vec[0][1]))
        {
            variable_one = s_maps->get_double(s_vec[0][1]);
        }
        else
        {
            variable_one = stod(s_vec[0][1]);
        }

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
            variable_two = stod(s_vec[0][3]);
        }
        switch (s_maps->get_int("map_operators", s_vec[0][2])) {
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

void Whilecommand::do_while()
{
    int index = 1;
    while(index <s_vec.size())
    {
        controler(s_maps).parsar(s_vec.at(index));
        index++;
    }
}
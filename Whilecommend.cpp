//
// Created by einat on 12/21/18.
//

#include "Whilecommend.h"
#include "controler.h"

Whilecommend::Whilecommend(vector<vector<string>> vec, maps* map)
{
    s_vec = vec;
    s_map = map;
}
void Whilecommend:: execute()
{
    bool flg = true;
    while (flg) {
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
            variable_one = stod(s_vec[0][1]);
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
            variable_two = stod(s_vec[0][3]);
        }
        switch (s_map->get_int("map_operators", s_vec[0][2])) {
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

void Whilecommend::do_while()
{
    int index = 1;
    while(index <s_vec.size())
    {
        controler(s_map).parsar(s_vec.at(index));
    }
}
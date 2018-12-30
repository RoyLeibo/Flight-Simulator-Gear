//
// Created by einat on 12/21/18.
//

#include "Equal.h"

Equal::Equal(string variable, double num, maps* map)
{
    this->variable = variable;
    this->s_num = num;
    this->s_maps = map;
}

//function that updating the value of the variable to s_num
void Equal::execute()
{

    s_maps->set_double(variable, s_num);
}
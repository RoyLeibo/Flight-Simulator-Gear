//
// Created by einat on 12/21/18.
//

#include "Equal.h"

// two questions: did we handle cases when some variable should be equal to other variable?
// diffrence in the use of set_double for "symbole_table" and for insert_double

Equal::Equal(string variable, double num, maps* map)
{
    this->variable = variable;
    this->s_num = num;
    this->s_maps = map;
}

//function that updating the value of the variable to s_num
void Equal::execute()
{
    cout <<"setting " << this->variable << " = " << this->s_num << endl;
    s_maps->set_double(variable, s_num);
}
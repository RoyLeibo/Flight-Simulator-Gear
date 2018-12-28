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
    this->s_map = map;
}
void Equal::execute()
{
    cout <<"setting " << this->variable << " = " << this->s_num << endl;
    s_map->set_double(variable, s_num);
}
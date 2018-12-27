//
// Created by einat on 12/21/18.
//

#include "Var.h"
using namespace std ;

Var::Var(string variable, maps* map)
{
    s_variable = variable;
    s_map = map;
}

void Var::execute ()
{
   bool check_variable = s_map->is_value_in_map("symbols_tables",s_variable);
   //if the variable already in the tables the var commend is not legal
   if(check_variable)
   {
       exit(1);
   }
   //add the variable to the map with out value
   else
   {
       s_map->insert_double("symbols_tables",s_variable,0.0);
   }

}

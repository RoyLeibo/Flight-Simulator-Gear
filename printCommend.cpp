//
// Created by einat on 12/21/18.
//

#include "printCommend.h"
printCommend::printCommend(string str_to_print)
{
    s_string_to_print = str_to_print;
}

void printCommend ::execute()
{
    cout<< s_string_to_print;
}
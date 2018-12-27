//
// Created by einat on 12/21/18.
//

#include "PrintCommand.h"
PrintCommand::PrintCommand(string str_to_print)
{
    s_string_to_print = str_to_print;
}

void PrintCommand ::execute()
{
    cout<< s_string_to_print<<endl;
}
//
// Created by einat on 12/21/18.
//

#include "PrintCommand.h"
PrintCommand::PrintCommand(string str_to_print)
{
    this->s_string_to_print = delete_quotation_marks(str_to_print) ;
}

//print the data members s_string_to_print
void PrintCommand ::execute()
{
    cout<< s_string_to_print<<endl;
}

//function that get the path and return string with out quotation marks
string PrintCommand::delete_quotation_marks(string s_path) {
    if (s_path[0] != '"') {
        return s_path ;
    }
    else {
        s_path.erase(0, 1) ;
        s_path.erase(s_path.length()-1, 1) ;
        return s_path ;
    }
}
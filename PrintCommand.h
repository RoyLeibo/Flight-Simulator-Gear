//
// Created by einat on 12/21/18.
//

#ifndef PORCJECT_PRINT_H
#define PORCJECT_PRINT_H


#include "command.h"

class PrintCommand : public command
{
    private:
        string s_string_to_print;

    public:
        PrintCommand(string str_to_print);
        virtual void execute();
};


#endif //PORCJECT_PRINT_H
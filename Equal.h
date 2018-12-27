//
// Created by einat on 12/21/18.
//

#ifndef PORCJECT_EQUAL_H
#define PORCJECT_EQUAL_H


#include "command.h"
#include "maps.h"
#include "IO.h"

class Equal: public command
{
private:
    string variable;
    double s_num;
    maps* s_map;

public:
    Equal(string variable, double num, maps* map);
    virtual void execute();

};


#endif //PORCJECT_EQUAL_H
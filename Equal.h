//
// Created by einat on 12/21/18.
//

#ifndef PORCJECT_EQUAL_H
#define PORCJECT_EQUAL_H


#include "Command.h"
#include "Maps.h"
#include "IO.h"

class Equal: public Command
{
private:
    string variable;
    double s_num;
    maps* s_maps;

public:
    Equal(string variable, double num, maps* map);
    virtual void execute();

};


#endif //PORCJECT_EQUAL_H
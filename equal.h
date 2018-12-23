//
// Created by einat on 12/21/18.
//

#ifndef PORCJECT_EQUAL_H
#define PORCJECT_EQUAL_H


#include "printCommend.h"
#include "maps.h"

class equal : public command
{
    private:
        string s_variable;
        double s_num;
        maps* s_map;

    public:
        equal(string variable, double num, maps* map);
        virtual void execute();
};


#endif //PORCJECT_EQUAL_H

//
// Created by einat on 12/21/18.
//

#ifndef PORCJECT_VAR_H
#define PORCJECT_VAR_H


#include "command.h"
#include "maps.h"

class Var : public command {
    private:
        string s_variable;
        maps* s_map;

    public:
        Var(string variable, maps* map);
        virtual void execute ();

};


#endif //PORCJECT_VAR_H

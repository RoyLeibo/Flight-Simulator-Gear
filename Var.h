//
// Created by einat on 12/21/18.
//

#ifndef PORCJECT_VAR_H
#define PORCJECT_VAR_H


#include "Command.h"
#include "Maps.h"

class Var : public Command {
    private:
        string s_variable;
        maps* s_maps;

    public:
        Var(string variable, maps* map);
        virtual void execute ();

};


#endif //PORCJECT_VAR_H

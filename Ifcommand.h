//
// Created by einat on 12/21/18.
//

#ifndef PORCJECT_IFcommand_H
#define PORCJECT_IFcommand_H


#include "Command.h"
#include "vector"

class Ifcommand :public Command
{
    private:
        vector<vector<string>> s_vec;
        maps* s_maps;
    public:
        Ifcommand(vector<vector<string>> vector, maps* map);
        void do_if();
        virtual void execute();
};


#endif //PORCJECT_IFcommand_H

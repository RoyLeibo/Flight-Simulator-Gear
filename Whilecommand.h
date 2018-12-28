//
// Created by einat on 12/21/18.
//

#ifndef PORCJECT_WHILEcommand_H
#define PORCJECT_WHILEcommand_H

#include "Command.h"
#include "Maps.h"
#include <vector>

class Whilecommand : public Command {
    private:
        vector<vector<string>> s_vec;
        maps* s_maps;

    public:
        Whilecommand(vector<vector<string>> vec, maps* map);
        void do_while();
        virtual void execute();

};


#endif //PORCJECT_WHILEcommand_H

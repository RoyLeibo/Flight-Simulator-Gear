//
// Created by einat on 12/21/18.
//

#ifndef PORCJECT_IFCOMMEND_H
#define PORCJECT_IFCOMMEND_H


#include "command.h"
#include "vector"

class Ifcommand :public command
{
    private:
        vector<vector<string>> s_vec;
        maps* s_map;
    public:
        Ifcommand(vector<vector<string>> vector, maps* map);
        void do_if();
        virtual void execute();
};


#endif //PORCJECT_IFCOMMEND_H

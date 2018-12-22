//
// Created by einat on 12/21/18.
//

#ifndef PORCJECT_IFCOMMEND_H
#define PORCJECT_IFCOMMEND_H


#include "command.h"
#include "vector"
#include "maps.h"

class ifcommend :public command
{
    private:
        vector<vector<string>> s_vec;
        maps* s_map;
    public:
        ifcommend(vector<vector<string>> vector, maps* map);
        void do_if();
        virtual void execute();
};


#endif //PORCJECT_IFCOMMEND_H

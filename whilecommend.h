//
// Created by einat on 12/21/18.
//

#ifndef PORCJECT_WHILECOMMEND_H
#define PORCJECT_WHILECOMMEND_H

#include "command.h"
#include "maps.h"
#include <vector>

class whilecommend : public command {
    private:
        vector<vector<string>> s_vec;
        maps* s_map;

    public:
        whilecommend(vector<vector<string>> vec, maps* map);
        void do_while();
        virtual void execute();

};


#endif //PORCJECT_WHILECOMMEND_H

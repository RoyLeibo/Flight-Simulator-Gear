//
// Created by einat on 12/21/18.
//

#ifndef PORCJECT_BIND_H
#define PORCJECT_BIND_H


#include "command.h"
#include "maps.h"

class bind : public command
{
    private:
        string s_key;
        string s_path;
        maps* map;
    public:
        bind(string key,string path,maps* map);
        virtual void execute();
};


#endif //PORCJECT_BIND_H

//
// Created by einat on 12/21/18.
//

#ifndef PORCJECT_BIND_H
#define PORCJECT_BIND_H


#include "Command.h"
#include "Maps.h"

class BindCommand : public Command
{
    private:
        string s_key;
        string s_path;
        maps* s_maps;
    public:
        BindCommand(string key,string path,maps* map);
        virtual void execute();
        string delete_quotation_marks(string s_path) ;
};


#endif //PORCJECT_BIND_H


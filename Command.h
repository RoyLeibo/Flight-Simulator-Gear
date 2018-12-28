//
// Created by roy on 12/17/18.
//

#ifndef UNTITLED11_COMMAND_H
#define UNTITLED11_COMMAND_H

#include <iostream>
#include <string>
#include "Maps.h"

using namespace std ;

class Command {

    public:
        virtual void execute()=0;
};


#endif //UNTITLED11_COMMAND_H

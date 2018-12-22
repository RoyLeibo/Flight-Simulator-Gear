//
// Created by roy on 12/17/18.
//

#ifndef UNTITLED11_OPENDATASERVER_H
#define UNTITLED11_OPENDATASERVER_H

#include "command.h"

class openDataServer: public command {
    private:
        double port ;
        double hz ;
    public:
        openDataServer(double port, double hz) ;
        virtual void execute() ;

};


#endif //UNTITLED11_OPENDATASERVER_H

//
// Created by roy on 12/17/18.
//

#ifndef UNTITLED11_CONNECT_H
#define UNTITLED11_CONNECT_H

#include "command.h"

class connect : public command{

    string IP ;
    int port ;

    connect(string IP, double port) ;
    virtual void execute() ;

};


#endif //UNTITLED11_CONNECT_H

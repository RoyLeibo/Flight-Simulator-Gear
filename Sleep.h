//
// Created by einat on 12/21/18.
//

#ifndef PORCJECT_SLEEP_H
#define PORCJECT_SLEEP_H


#include "Command.h"

class Sleep : public Command
{
    private:
    double s_time;

    public:
    Sleep(double time);
    virtual void execute();
};


#endif //PORCJECT_SLEEP_H

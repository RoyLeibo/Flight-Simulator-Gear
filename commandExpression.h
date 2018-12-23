//
// Created by einat on 12/22/18.
//

#ifndef UNTITLED11_COMMENDEXPRESSION_H
#define UNTITLED11_COMMENDEXPRESSION_H

#include "expression.h"
#include "command.h"
class commandExpression : public expression
{
    private:
        command* s_command;

    public:
        commandExpression(command* command);
        virtual void calculate() ;

};


#endif //UNTITLED11_COMMENDEXPRESSION_H

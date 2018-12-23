//
// Created by einat on 12/22/18.
//

#include "commandExpression.h"
commandExpression::commandExpression(command* command)
{
    s_command = command;
}
void commandExpression:: calculate()
{
    s_command->execute();
}
//
// Created by roy on 12/18/18.
//

#ifndef UNTITLED11_DIV_H
#define UNTITLED11_DIV_H

#include "binaryExpression.h"

class Div: public binaryExpression {
    double leftChild ;
    double rightChild ;

public:
    Div(double leftChild, double rightChild) ;
    double calculate() ;

};


#endif //UNTITLED11_DIV_H

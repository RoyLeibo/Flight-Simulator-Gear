//
// Created by roy on 12/18/18.
//

#ifndef UNTITLED11_MINUS_H
#define UNTITLED11_MINUS_H

#include "binaryExpression.h"

class Minus: public binaryExpression {
    double leftChild ;
    double rightChild ;

public:
    Minus(double leftChild, double rightChild) ;
    double calculate() ;

};


#endif //UNTITLED11_MINUS_H

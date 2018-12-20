//
// Created by roy on 12/18/18.
//

#ifndef UNTITLED11_MUL_H
#define UNTITLED11_MUL_H


#include "binaryExpression.h"

class Mul: public binaryExpression {
    double leftChild ;
    double rightChild ;

public:
    Mul(double leftChild, double rightChild) ;
    double calculate() ;

};


#endif //UNTITLED11_MUL_H

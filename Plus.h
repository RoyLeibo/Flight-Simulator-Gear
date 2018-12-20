//
// Created by roy on 12/18/18.
//

#ifndef UNTITLED11_PLUS_H
#define UNTITLED11_PLUS_H

#include "binaryExpression.h"

class Plus: public binaryExpression {
    double leftChild ;
    double rightChild ;

public:
    Plus(double leftChild, double rightChild) ;
    double calculate() ;

};


#endif //UNTITLED11_PLUS_H

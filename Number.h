//
// Created by roy on 12/19/18.
//

#ifndef UNTITLED11_NUMBER_H
#define UNTITLED11_NUMBER_H

#include "expression.h"


class Number: public expression {
    double num ;

public:
    Number(double num) ;
    double calculate() ;
};


#endif //UNTITLED11_NUMBER_H

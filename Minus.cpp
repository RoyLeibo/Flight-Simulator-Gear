//
// Created by roy on 12/18/18.
//

#include "Minus.h"

Minus::Minus(double leftChild, double rightChild) {
    this->leftChild = leftChild ;
    this->rightChild = rightChild ;
}
double Minus::calculate() {
    return (leftChild - rightChild) ;
}

//
// Created by roy on 12/18/18.
//

#include "Mul.h"

Mul::Mul(double leftChild, double rightChild) {
    this->leftChild = leftChild ;
    this->rightChild = rightChild ;
}
double Mul::calculate() {
    return (leftChild * rightChild) ;
}
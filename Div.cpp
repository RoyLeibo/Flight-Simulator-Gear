//
// Created by roy on 12/18/18.
//

#include "Div.h"

Div::Div(double leftChild, double rightChild) {
    this->leftChild = leftChild ;
    this->rightChild = rightChild ;
}
double Div::calculate() {
    return (leftChild / rightChild) ;
}
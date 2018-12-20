//
// Created by roy on 12/18/18.
//

#include "Plus.h"

Plus::Plus(double leftChild, double rightChild) {
    this->leftChild = leftChild ;
    this->rightChild = rightChild ;
}
double Plus::calculate() {
    return (leftChild + rightChild) ;
}
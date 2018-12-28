//
// Created by roy on 12/18/18.
//

#ifndef UNTITLED11_DIJKSTRA_H
#define UNTITLED11_DIJKSTRA_H

#include <iostream>
#include <string>
#include <stack>
#include <queue>
#include <map>
#include <vector>
#include "maps.h"

using namespace std ;

class dijkstra {

public:
    double calc (string expression, maps* myMaps) ;

private:
    vector<string> convert_to_vector (string expression, maps* myMaps) ;
    vector<string> shunting_Yard(vector <string> expression, maps* myMaps) ;
    double postFixEva(vector <string> expression) ;
    string variables_to_double(string expression, maps* myMaps) ;

};


#endif //UNTITLED11_DIJKSTRA_H

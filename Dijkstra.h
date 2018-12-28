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
#include "Maps.h"

using namespace std ;

class dijkstra {

public:
    double calc (string expression, maps* s_maps) ;

private:
    vector<string> convert_to_vector (string expression, maps* s_maps) ;
    vector<string> shunting_Yard(vector <string> expression, maps* s_maps) ;
    double postFixEva(vector <string> expression) ;
    string variables_to_double(string expression, maps* s_maps) ;

};


#endif //UNTITLED11_DIJKSTRA_H

//
// Created by einat on 12/17/18.
//

#ifndef PORCJECT_CONTROLER_H
#define PORCJECT_CONTROLER_H

#include <vector>
#include <string>
#include <map>
#include "maps.h"
using namespace std;

class controler
{
    private:
        maps* s_map;
        //controler* control;
        bool string_isdigit(string str);
        vector<string> create_new_vector(vector<string> line, int start, int end);
        void command_while_if(vector<string> vec, bool flg);
        //void cmmand_if(vector<string> vec);
    public:
      controler();
      controler(maps* map);
      vector<std::string> lexes(string line);
      void parsar(vector<string> vec);
      ~controler();
};


#endif //PORCJECT_CONTROLER_H

#include <iostream>
#include <istream>
#include <string.h>
#include <fstream>
#include "controler.h"
using namespace std;

int main(int argc, char* argv[] ) {
    controler* control = new controler();
    ifstream pointer;
    //open the file
    pointer.open(argv[2]);
    string line;
    int counter = 0;
    //read line by line until the end of file
    while(getline(pointer,line))
    {
        if (line.substr(0, 5) == "while" && line.substr(0,2) == "if")
        {
            counter++;
            while (line[line.length() - 1] != '}' && counter != 0)
            {
                line = line + ';';
                getline(pointer, line);
                if(line[line.length()-1] == '{')
                {
                    counter++;
                }
                else if(line[line.length()-1] == '}')
                {
                    counter--;
                }
            }

        }
        control->parsar(control->lexes(line));

    }
    delete(control);
    return 0;
}
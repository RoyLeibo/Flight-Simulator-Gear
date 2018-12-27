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
    pointer.open(argv[1]);
    string line;
    string line_two;
    int counter = 0;
    //read line by line until the end of file
    while(getline(pointer,line) && line != "")
    {
        if (line.substr(0, 5) == "while" || line.substr(0,2) == "if")
        {
            if(line[line.length()-1] == '{')
            {
                counter++;
            }
            while ((line[line.length() - 1] != ';' && line[line.length() - 1]  != '}') || counter != 0)
            {
                getline(pointer, line_two);
                if (line_two == "{" || line_two == "}")
                {
                    line += line_two +";";
                    if(line_two == "}")
                    {
                        counter--;
                    }
                    else
                    {
                        counter++;
                    }
                }
                if (line_two != "" && line_two != "{" && line_two != "}")
                {
                    if(line[line.length()-1] != ';')
                    {
                        line += ";";
                    }
                    line += line_two;

                }
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
  //  delete(control);
    return 0;
}
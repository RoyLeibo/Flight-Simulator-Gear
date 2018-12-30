#include <iostream>
#include <istream>
#include <string.h>
#include <fstream>
#include "Controler.h"
using namespace std;

int main(int argc, char* argv[]) {
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
        //if the line it is while command or if keep reading until the end of end of the scope
        if (line.substr(0, 5) == "while" || line.substr(0,2) == "if")
        {
            //if the end of the line finish in { and one to the counter
            if(line[line.length()-1] == '{')
            {
                counter++;
            }
            //keep read while the counter different from zero and the lest cher was different fro ! or }
            while ((line[line.length() - 1] != ';' && line[line.length() - 1]  != '}') || counter != 0)
            {
                getline(pointer, line_two);
                //if the line is { or }
                if (line_two == "{" || line_two == "}")
                {
                    //add line to the previous line and mark the end of the line with ;
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
                //if the line different and not space
                if (line_two != "" && line_two != "{" && line_two != "}")
                {
                    //if the end of the previous line dont mark with ; add it
                    if(line[line.length()-1] != ';')
                    {
                        line += ";";
                    }
                    //and add the next line
                    line += line_two;

                }
                //if the line is ends with } add one to counter
                if(line[line.length()-1] == '{')
                {
                    counter++;
                }
                //it the kine is ends with { subtract one from counter
                else if(line[line.length()-1] == '}')
                {
                    counter--;
                }
            }

        }
        //interpret the line or scope
        control->parsar(control->lexes(line));
    }
    pointer.close();
  //  delete(control);
    return 0;
}
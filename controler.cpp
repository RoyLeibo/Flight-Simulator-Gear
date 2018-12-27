//
// Created by einat on 12/17/18.
//

#include "controler.h"
#include "dijkstra.h"
#include "command.h"
#include "openDataServer.h"
#include "Connect.h"
#include "Var.h"
#include "BindCommand.h"
#include "PrintCommand.h"
#include "Equal.h"
#include "Sleep.h"
#include "Whilecommend.h"
#include "Ifcommand.h"

#define ONE 1
#define TWO 2
#define ZERO 0

controler::controler()
{
    s_map = new maps();
}

controler::controler(maps* map)
{
    s_map = map;
}

//get string
//divid the string to
vector<std::string> controler::lexes(string line)
{
    vector<string> vector;
    int index = ZERO;
    char current_char;
    char next_char;
    string word;
    //check if there spaces in the start of the line
    while(isspace(line[index]))
    {
        index++;
    }
    for(int index = ZERO; index < line.length()- ONE; index++)
    {
        current_char = line[index];
        next_char = line[index + 1];
        if(current_char == '{' || current_char== '}')
        {
            if(word != "") {
                vector.push_back(word);
                word = "";
            }
            word = "";
            word =+ current_char;
            vector.push_back(word);
            word = "";

            //vector.push_back(to_string(current_char));
        }
        else if(current_char == ',' )
        {
            vector.push_back(word);
            word = "";
        }
        else if(current_char == '"')
        {
            if(word[0] == '"')
            {
                word += current_char;
                vector.push_back(word);
                word = "";
            }
            else
            {
                vector.push_back(word);
                word = "";
                //word = current_char;
            }
        }
        else if(current_char == '=')
        {
            if(next_char == '=')
            {
                if(word != "")
                {
                    vector.push_back(word);
                }
                vector.push_back("==");
                word = "";
                index++;
            }
            else
            {
                if(word != "")
                {
                    vector.push_back(word);
                }
                vector.push_back("=");
                word = "";
            }
        }
        else if((isspace(current_char) && ((isalpha(next_char) || isdigit(next_char)) || (next_char == '(')))
        && ((isdigit(word[word.length() - ONE]) || isalpha(word[word.length() - ONE])) || word[word.length() - ONE] == ')' ))
        {
            vector.push_back(word);
            word = "";
        }
        else if((((current_char == '<' || current_char ==  '>')  ||  current_char == ';') || current_char == '!'))
        {
            if(next_char != '=' || current_char == ';')
            {
                if(word != "") {
                    vector.push_back(word);
                    word = "";
                }
                word += current_char;
                vector.push_back(word);
                word = "";
            }
            else
            {
                vector.push_back(word);
                word = "";
                word = word + current_char + next_char;
                vector.push_back(word);
                word = "";
                index++;
            }
        }
        else if(!isspace(current_char))
        {
            word +=  current_char;
        }
        if(index == line.length()-TWO && next_char != '"')
        {

            word +=  next_char;
        }

    }
    vector.push_back(word);
    return vector;
}

void controler::parsar(vector<string> vec)
{
    int index = ONE;
    //check if the first word in the string is commend
    bool is_commend = s_map->is_value_in_map("map_command",vec.at(ZERO));
    //if the first word is not commend
    if(!is_commend)
    {
        //check if the word find in the symbols table
        bool is_variable_map_symbols = s_map->is_value_in_map("symbols_tables",vec.at(ZERO));
        bool is_variable_map_path =  s_map-> is_value_in_map("map_path",vec.at(ZERO));
        if(!is_variable_map_symbols && !is_variable_map_path)
        {
            exit(ONE);
        }
        //if yet
        else
        {
            if(vec.at(index) == "=")
            {
               Equal(vec.at(ZERO),dijkstra().calc(vec.at(TWO),s_map),s_map).execute();
            }
            else
            {
                exit(ONE);
            }
        }
    }
    else
    {
        int commend = s_map->get_int("map_command",vec.at(ZERO));
        switch(commend)
        {
            //if the commend is openDataServer
            case 1:
                openDataServer(dijkstra().calc(vec.at(ONE),s_map),
                        dijkstra().calc(vec.at(TWO),s_map), s_map).execute();
                break;
            //if the commend is connect
            case 2:
                Connect(vec.at(ONE),dijkstra().calc(vec.at(TWO),s_map), s_map).execute();
                break;
            //if the commend is var
            case 3:
                if(vec.size() <= 4) {
                    Var(vec.at(index++), s_map).execute();
                    //if it only site variable
                    if (index >= vec.size()) {
                        break;
                    }
                }
                else
                {
                    index++;
                }
                //the command =
            case 4:
                index++;
                //if the next command is bind
                if(vec.at(index) == "bind")
                {
                    BindCommand(vec.at(index - TWO),vec.at(index + ONE),s_map).execute();
                }
                //is it equals to variable / number/ math phrase
                else
                {
                   Equal(vec.at(index - TWO),dijkstra().calc(vec.at(index),s_map), s_map).execute();
                }
                break;
            //if the commend is print
            case 5:
                //it is number
                if(string_isdigit(vec.at(index)))
                {

                    PrintCommand(vec.at(index)).execute();
                }
                //it is variable that found in symbole tables
                else if(s_map->is_value_in_map("symbols_tables",vec.at(index)))
                {
                    PrintCommand(to_string(s_map->get_double(vec.at(index)))).execute();
                }
                //it is variable the have on hem bind
                else if(s_map->is_value_in_map("map_path", vec.at(index)))
                {
                    PrintCommand(to_string(s_map->get_double(vec.at(index)))).execute();
                }
                //if it string
                else if(vec.at(index)[0] == '"')
                {
                   PrintCommand(vec.at(index)).execute();
                }
                //it is phrase
                else
                {
                    PrintCommand(to_string(dijkstra().calc(vec.at(index),s_map))).execute();
                }
                break;
            //commend sleep
            case 6:
                Sleep(dijkstra().calc(vec.at(index),s_map)).execute();
                break;

            //commend while
            case 7:
                command_while_if(vec, true);
                break;
            //commend if
            case 8:
                command_while_if(vec, false);
                break;

        }
    }
}

bool controler::string_isdigit(string str)
{
    for(int i = ZERO; i < str.length(); i++)
    {
        if(!isdigit(str[i]))
        {
            return false;
        }
    }
    return true;
}

vector<string> controler::create_new_vector(vector<string> line, int start, int end)
{
    vector<string> res;
    while (start <= end)
    {
        res.push_back(line.at(start));
        start++;
    }

    return res;

}

void controler::command_while_if(vector<string> vec, bool flg)
{
    vector<vector<string>> commend;
    int num_vec;
    int num_index;
    int counter = 1;
    int start = ZERO;
    int end = ZERO;
    int time = 0;

    while(counter < vec.size())
    {
        if(vec.at(counter) == "if" || vec.at(counter) == "while")
        {
            start = counter;
            while(vec.at(counter-1) != "}" || time != 0)
            {
                if(vec.at(counter) == "{")
                {
                    time++;
                }
                else if(vec.at(counter) == "}")
                {
                    time--;
                }
                    counter++;

            }
            end =  counter - ONE;
            commend.push_back(create_new_vector(vec,start,end));
            start = counter + 1;
        }

        else if(vec.at(counter) == ";")
        {
            end =  counter - ONE;
            commend.push_back(create_new_vector(vec,start,end));
            start = counter + ONE;
        }
        counter++;
    }
    if (flg == true)
    {
        Whilecommend(commend, s_map).execute();
    }
    else
    {
       Ifcommand(commend, s_map).execute();
    }
}

controler ::~controler(){}


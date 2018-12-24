//
// Created by einat on 12/21/18.
//

#include "Sleep.h"
#include <chrono>

Sleep:: Sleep(double time)
{
    s_time = time;
}
void Sleep:: execute()
{
    chrono::seconds(s_time);
}
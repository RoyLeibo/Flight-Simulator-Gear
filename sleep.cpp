//
// Created by einat on 12/21/18.
//

#include "sleep.h"
#include <chrono>

sleep::sleep(double time)
{
    s_time = time;
}
void sleep:: execute()
{
    chrono::seconds(s_time);
}
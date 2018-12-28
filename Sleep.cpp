//
// Created by einat on 12/21/18.
//

#include "Sleep.h"
#include <chrono>
#include <thread>
using namespace std::this_thread; // sleep_for, sleep_until
using namespace std::chrono; // nanoseconds, system_clock, seconds


Sleep:: Sleep(double time)
{
    this->s_time = time;
}
void Sleep:: execute() {
    sleep_for(milliseconds((int)s_time));
}
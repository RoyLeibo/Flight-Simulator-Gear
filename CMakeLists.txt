cmake_minimum_required(VERSION 3.12.3)
project(untitled11)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS -pthread)

add_executable(untitled11 main.cpp Command.h openDataServer.cpp openDataServer.h Connect.cpp
        Connect.h Dijkstra.cpp Dijkstra.h Maps.cpp Maps.h BindCommand.cpp BindCommand.h Controler.cpp
        Controler.h Equal.cpp Equal.h Ifcommand.cpp Ifcommand.h Var.cpp Var.h Whilecommand.cpp
        Whilecommand.h Sleep.cpp Sleep.h PrintCommand.cpp PrintCommand.h IO.cpp IO.h Equal.cpp Equal.h Enterc.cpp Enterc.h)
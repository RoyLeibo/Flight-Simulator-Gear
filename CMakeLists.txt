cmake_minimum_required(VERSION 3.12.3)
project(untitled11)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS -pthread)

add_executable(untitled11 main.cpp command.h openDataServer.cpp openDataServer.h Connect.cpp
        Connect.h dijkstra.cpp dijkstra.h  maps.cpp maps.h BindCommand.cpp BindCommand.h controler.cpp
        controler.h Equal.cpp Equal.h Ifcommand.cpp Ifcommand.h Var.cpp Var.h Whilecommend.cpp
        Whilecommend.h Sleep.cpp Sleep.h PrintCommand.cpp PrintCommand.h IO.cpp IO.h Equal.cpp Equal.h Enterc.cpp Enterc.h)
cmake_minimum_required(VERSION 3.13)
project(untitled11)

set(CMAKE_CXX_STANDARD 14)

add_executable(untitled11 main.cpp command.h openDataServer.cpp openDataServer.h connect.cpp
        connect.h dijkstra.cpp dijkstra.h expression.h binaryExpression.h Plus.cpp Plus.h
        binaryExpression.cpp Minus.cpp Minus.h Mul.cpp Mul.h Div.cpp Div.h Number.cpp Number.h
        maps.cpp maps.h bind.cpp bind.h controler.cpp controler.h equal.cpp equal.h ifcommend.cpp ifcommend.h
        var.cpp var.h whilecommend.cpp whilecommend.h sleep.cpp sleep.h )
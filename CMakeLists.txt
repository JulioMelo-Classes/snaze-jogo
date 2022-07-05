cmake_minimum_required(VERSION 3.5)
project(Snaze VERSION 0.1 LANGUAGES CXX )

include_directories( include )
set (CMAKE_CXX_FLAGS "-fsanitize=address -g")

add_executable( snaze
                src/SnakeGame.cpp
                src/main.cpp
                src/Player.cpp
                )
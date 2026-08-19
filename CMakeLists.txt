cmake_minimum_required(VERSION 4.2)
project(guidance_sim_cpp)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(guidance_sim_cpp
        main.cpp
        main.h
        maths.cpp
)



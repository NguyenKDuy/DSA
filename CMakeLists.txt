cmake_minimum_required(VERSION 3.27)
project(init)

set(CMAKE_CXX_STANDARD 11)

add_executable(init main.cpp
        kNN.cpp
        mnist.csv
)

cmake_minimum_required(VERSION 3.14)
project(sparse-matrix-JuanGA12)

set(CMAKE_CXX_STANDARD 17)

add_executable(sparse-matrix-JuanGA12 main.cpp tester/tester.cpp mocker/mocker.cpp)
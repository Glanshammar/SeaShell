cmake_minimum_required(VERSION 3.27)
project(SeaShell)

set(CMAKE_CXX_STANDARD 20)

add_executable(SeaShell "main.cpp"
                        "global.hpp")

target_link_libraries(SeaShell -static)
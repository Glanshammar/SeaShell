cmake_minimum_required(VERSION 3.27)
project(SeaShell)

set(CMAKE_CXX_STANDARD 20)


include_directories(
        "C:/C++/boost_1_84_0/"
        "C:/C++/openssh/"
        "C:/C++/freerdp-3.0.0/include/"
        "C:/C++/openssl-3.2.0/include/"
        "C:/C++/yaml-cpp-0.8.0/include/")

add_executable(SeaShell
        "main.cpp"
        "global.hpp"
        "functions.hpp"
        "functions/files/execute.cpp"
        "functions/files/execute.hpp")

target_link_libraries(SeaShell
        -static)
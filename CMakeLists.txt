cmake_minimum_required(VERSION 3.27)
project("SeaShell" VERSION 0.1 DESCRIPTION "The best shell ever!")

set(CMAKE_CXX_STANDARD 20)

include_directories(
        "C:/C++/boost_1_84_0/"
        "C:/C++/freerdp-3.0.0/include/"
        "C:/C++/openssl-3.2.0/include/"
        "C:/C++/libssh2-1.11.0/include/"
        "C:/C++/cryptopp890/"
        "C:/C++/yaml-cpp-0.8.0/include/")

link_directories(
        "C:/C++/boost_1_84_0/libs"
)

add_executable(SeaShell
        "main.cpp"
        "global.hpp"
        "functions client/functions.hpp"
        "functions client/files/execute.cpp"
        "functions client/files/execute.hpp"
        "functions client/networking/client.cpp"
        "functions client/networking/client.hpp")

add_executable(SeaServer
        "functions server/server.cpp"
        "functions server/helloworld.cpp"
        "functions server/helloworld.hpp"
        "functions server/networking/sendtoclient.cpp"
        "functions server/networking/sendtoclient.hpp"
        "functions server/functions.hpp")

target_link_libraries(SeaShell
        -static
        Ws2_32.lib)

target_link_libraries(SeaServer
        -static
        Ws2_32.lib
        iphlpapi.lib)

cmake_minimum_required(VERSION 3.27)
project("SeaShell" VERSION 0.1 DESCRIPTION "The best shell ever!")

set(CMAKE_CXX_STANDARD 20)

find_package(Python REQUIRED COMPONENTS Development)

include_directories(
        "C:/C++/boost_1_85_0/"
        "C:/C++/freerdp-3.5.1/include/"
        "C:/C++/openssl-3.2.1/include/"
        "C:/C++/libssh2-1.11.0/include/"
        "C:/C++/cryptopp890/"
        "C:/C++/ncurses-6.5/include/"
        "C:/C++/curl-8.7.1/include/"
        "C:/C++/yaml-cpp-0.8.0/include/"
        "C:/Users/Mondus/AppData/Local/Programs/Python/Python312/include"
)


link_directories(
        "C:/C++/boost_1_85_0/libs"
)

add_executable(SeaShell
        "global.hpp"
        "SeaShell/seashell.cpp"
        "SeaShell/functions.hpp"
        "SeaShell/files/execute.cpp"
        "SeaShell/files/execute.hpp"
        "SeaShell/networking/client.cpp"
        "SeaShell/networking/client.hpp"
        "global.cpp"
        "SeaShell/files/python.cpp"
        "SeaShell/files/python.hpp"
)

add_executable(SeaServer
        "global.hpp"
        "SeaServer/functions.hpp"
        "SeaServer/server.cpp"
        "SeaServer/helloworld.cpp"
        "SeaServer/helloworld.hpp"
        "SeaServer/networking/clientsend.cpp"
        "SeaServer/networking/clientsend.hpp"
        "global.cpp"
)

target_link_libraries(SeaShell
        -static
        Ws2_32.lib
        ${Boost_LIBRARIES}
        ${Python_LIBRARIES}
)

target_link_libraries(SeaServer
        -static
        Ws2_32.lib
        iphlpapi.lib
        ${Boost_LIBRARIES}
)
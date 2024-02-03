cmake_minimum_required(VERSION 3.27)
project("SeaShell" VERSION 0.1 DESCRIPTION "The best shell ever!")

set(CMAKE_CXX_STANDARD 20)

include_directories(
        "C:/C++/boost_1_84_0/"
        "C:/C++/freerdp-3.0.0/include/"
        "C:/C++/openssl-3.2.0/include/"
        "C:/C++/libssh2-1.11.0/include/"
        "C:/C++/cryptopp890/"
        "C:/C++/ncurses-6.3/include/"
        "C:/C++/curl-8.5.0/include/"
        "C:/C++/yaml-cpp-0.8.0/include/")

link_directories(
        "C:/C++/boost_1_84_0/libs"
)

add_executable(SeaShell
        "global.hpp"
        "SeaShell/seashell.cpp"
        "SeaShell/functions.hpp"
        "SeaShell/files/execute.cpp"
        "SeaShell/files/execute.hpp"
        "SeaShell/networking/client.cpp"
        "SeaShell/networking/client.hpp")

add_executable(SeaServer
        "global.hpp"
        "SeaServer/functions.hpp"
        "SeaServer/server.cpp"
        "SeaServer/helloworld.cpp"
        "SeaServer/helloworld.hpp"
        "SeaServer/networking/clientsend.cpp"
        "SeaServer/networking/clientsend.hpp")

add_executable(SeaInstaller
        "global.hpp"
        "SeaShell/installer.cpp")

target_link_libraries(SeaShell
        -static
        Ws2_32.lib)

target_link_libraries(SeaServer
        -static
        Ws2_32.lib
        iphlpapi.lib)

target_link_libraries(SeaInstaller
        -static)
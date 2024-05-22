cmake_minimum_required(VERSION 3.27)
project("SeaShell" VERSION 0.1)


set(CMAKE_CXX_STANDARD 20)
set(POCO_ROOT "C:/C++/poco-1.13.3/")

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    message("Building in Debug mode")
    set(POCO_LIB_DIR "${POCO_ROOT}/build-debug/lib/")
    set(Poco_DIR "${POCO_ROOT}/build-debug/Poco")
    set(POCO_DLL_DIR "${POCO_ROOT}/build-debug/bin/")
elseif(CMAKE_BUILD_TYPE STREQUAL "Release")
    message("Building in Release mode")
    set(POCO_LIB_DIR "${POCO_ROOT}/build-release/lib/")
    set(Poco_DIR "${POCO_ROOT}/build-release/Poco")
    set(POCO_DLL_DIR "${POCO_ROOT}/build-release/bin/")
else()
    message("Unknown build type: ${CMAKE_BUILD_TYPE}")
endif()

file(COPY ${POCO_DLL_DIR} DESTINATION ${CMAKE_BINARY_DIR})

find_package(Python REQUIRED COMPONENTS Development)
find_package(Poco REQUIRED
        Foundation
        Util
        Net
        XML
        JSON
        Data
)


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

include_directories(
        ${POCO_ROOT}/Foundation/include
        ${POCO_ROOT}/Util/include
        ${POCO_ROOT}/Net/include
        ${POCO_ROOT}/XML/include
        ${POCO_ROOT}/JSON/include
        ${POCO_ROOT}/Data/include
)

link_directories(
        "C:/C++/boost_1_85_0/libs"
        ${POCO_LIB_DIR}
)

set(POCO_LIBS
        Poco::Foundation
        Poco::Util
        Poco::Net
        Poco::XML
        Poco::JSON
        Poco::Data
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
        "SeaShell/pocotest.cpp"
        "SeaShell/pocotest.hpp"
)

add_executable(SeaServer
        "global.hpp"
        "SeaServer/functions.hpp"
        "SeaServer/server.cpp"
        "SeaServer/networking/clientsend.cpp"
        "SeaServer/networking/clientsend.hpp"
        "global.cpp"
)

target_link_libraries(SeaShell
        PUBLIC
        Ws2_32
        ${Python_LIBRARIES}
        ${POCO_LIBS}
)

target_link_libraries(SeaServer
        PUBLIC
        Ws2_32
        iphlpapi
        ${POCO_LIBS}
)

target_include_directories(SeaShell PRIVATE ${OPENSSL_INCLUDE_DIR})
target_include_directories(SeaServer PRIVATE ${OPENSSL_INCLUDE_DIR})
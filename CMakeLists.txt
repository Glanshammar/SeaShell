cmake_minimum_required(VERSION 3.28)
project("SeaShell" VERSION 0.3)
set(CMAKE_CXX_STANDARD 20)
set(PROJECT_ROOT ${CMAKE_CURRENT_SOURCE_DIR})
set(CMAKE_VERBOSE_MAKEFILE ON)

set(USE_MYSQL ON)
set(MYSQL_VERSION "9.1")
set(WINDOWS_SDK_VERSION "10.0.22621.0")
set(PYTHON_VERSION "3.13")
string(REPLACE "." "" PYTHON_VERSION_NO_DOT ${PYTHON_VERSION}) #Remove the dot from the Python version, to make it work with Python paths

if(WIN32)
    set(USER_HOME $ENV{USERPROFILE})
    add_definitions(-DWIN32_LEAN_AND_MEAN)
elseif(UNIX)
    set(USER_HOME $ENV{HOME})
endif()

if(NOT USER_HOME)
    message(FATAL_ERROR "Could not determine the user's home directory")
endif()

set(VCPKG_DIR "${USER_HOME}/.vcpkg-clion/SeaShell")
set(CMAKE_TOOLCHAIN_FILE "${VCPKG_DIR}/scripts/buildsystems/vcpkg.cmake" CACHE STRING "")
link_directories("${VCPKG_DIR}/installed/x64-windows/debug/lib")

include_directories(
        #"${USER_HOME}/CLionProjects/VistaFramework/Vista/include/Vista" #Vista Include
        "${USER_HOME}/AppData/Local/Programs/Python/Python${PYTHON_VERSION_NO_DOT}/include" #Python Include
)

if(WIN32)
    include_directories(
            "C:/Program Files (x86)/Windows Kits/10/Include/${WINDOWS_SDK_VERSION}/" #Windows headers
    )
endif()

# vcpkg packages
find_package(CURL CONFIG REQUIRED)
find_package(OpenSSL REQUIRED)
find_package(Libssh2 CONFIG REQUIRED)
find_package(Poco REQUIRED COMPONENTS
        Foundation
        Util
        Net
        XML
        JSON
        Data
        Zip
        MongoDB
        Redis
)

add_executable(SeaShell
        "SeaShell/global.cpp" "SeaShell/global.hpp"
        "SeaShell/seashell.cpp" "SeaShell/functions.hpp"
        "SeaShell/files/execute.cpp" "SeaShell/files/execute.hpp"
        "SeaShell/files/python.cpp" "SeaShell/files/python.hpp"
        "SeaShell/files/encrypt.cpp" "SeaShell/files/encrypt.hpp"
        "SeaShell/networking/clientsend.cpp" "SeaShell/networking/clientsend.hpp"
        "SeaShell/files/filesystem.cpp" "SeaShell/files/filesystem.hpp"
        "SeaShell/help.cpp" "SeaShell/help.hpp"
        "SeaShell/networking/ip.cpp" "SeaShell/networking/ip.hpp"
        "SeaShell/files/zip.cpp" "SeaShell/files/zip.hpp"
)

set(POCO_LIBS
        Poco::Foundation
        Poco::Util
        Poco::Net
        Poco::XML
        Poco::JSON
        Poco::Data
        Poco::Zip
        Poco::MongoDB
        Poco::Redis
)

#set(VistaLib "${USER_HOME}/CLionProjects/VistaFramework/cmake-build-release/VistaFramework.lib")
set(PythonLib_DEBUG "${USER_HOME}/AppData/Local/Programs/Python/Python${PYTHON_VERSION_NO_DOT}/libs/python${PYTHON_VERSION_NO_DOT}_d.lib")
set(PythonLib_RELEASE "${USER_HOME}/AppData/Local/Programs/Python/Python${PYTHON_VERSION_NO_DOT}/libs/python${PYTHON_VERSION_NO_DOT}.lib")

target_link_libraries(SeaShell
        PUBLIC
        Ws2_32
        $<$<CONFIG:Debug>:${PythonLib_DEBUG}>
        $<$<CONFIG:Release>:${PythonLib_RELEASE}>
        ${POCO_LIBS}
        #${VistaLib}
        CURL::libcurl
        OpenSSL::SSL
        OpenSSL::Crypto
        Libssh2::libssh2
)

if(USE_MYSQL)
    set(MYSQL_LIB_PATH "C:/Program Files/MySQL/MySQL Server ${MYSQL_VERSION}/lib/mysqlclient.lib")
    set(MYSQL_INCLUDE_PATH "C:/Program Files/MySQL/MySQL Server ${MYSQL_VERSION}/include")

    if(EXISTS ${MYSQL_LIB_PATH})
        target_link_libraries(SeaShell PUBLIC ${MYSQL_LIB_PATH})
        message("-- MySQL library found: " ${MYSQL_LIB_PATH})
    else()
        message(WARNING "MySQL library not found at ${MYSQL_LIB_PATH}")
    endif()

    if(IS_DIRECTORY ${MYSQL_INCLUDE_PATH})
        include_directories(${MYSQL_INCLUDE_PATH})
        message("-- MySQL includes found: " ${MYSQL_INCLUDE_PATH})
    else()
        message(WARNING "MySQL include directory not found at ${MYSQL_INCLUDE_PATH}")
    endif()
endif()
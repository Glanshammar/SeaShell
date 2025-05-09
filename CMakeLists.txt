# Basic Project Setup
cmake_minimum_required(VERSION 3.21)
project("SeaShell" VERSION 0.3)

# Build Configuration
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE "Release" CACHE STRING "Build type" FORCE)
endif()

# Set C++ standard using modern approach
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Project Options
option(USE_MYSQL "Enable MySQL support" OFF)
option(CMAKE_VERBOSE_MAKEFILE "Generate verbose makefiles" ON)

# Platform Detection and Variables
if(WIN32)
    set(USER_HOME $ENV{USERPROFILE})
elseif(UNIX)
    set(USER_HOME $ENV{HOME})
endif()

if(NOT USER_HOME)
    message(FATAL_ERROR "Could not determine the user's home directory")
endif()

# Project Variables
set(PROJECT_ROOT ${CMAKE_CURRENT_SOURCE_DIR})
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

# Dependency Management
include(FetchContent)
set(FETCHCONTENT_QUIET FALSE)

# Find Required Packages
find_package(fmt CONFIG REQUIRED)
find_package(CURL CONFIG REQUIRED)
find_package(OpenSSL CONFIG REQUIRED)
find_package(Libssh2 CONFIG REQUIRED)
find_package(Poco CONFIG COMPONENTS
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

# Find Python
set(PYTHON_VERSION "3.13")
find_package(Python3 ${PYTHON_VERSION} COMPONENTS Development QUIET)
if(NOT Python3_FOUND)
    message(STATUS "Python ${PYTHON_VERSION} not found. Trying any available Python3...")
    find_package(Python3 COMPONENTS Development REQUIRED)
endif()

# Handle MySQL
if(USE_MYSQL)
    set(MYSQL_VERSION "9.1")
    find_package(MySQL QUIET)
    
    if(NOT MYSQL_FOUND)
        if(WIN32)
            set(MYSQL_LIB_PATH "C:/Program Files/MySQL/MySQL Server ${MYSQL_VERSION}/lib/mysqlclient.lib")
            set(MYSQL_INCLUDE_PATH "C:/Program Files/MySQL/MySQL Server ${MYSQL_VERSION}/include")
            
            if(EXISTS ${MYSQL_LIB_PATH} AND IS_DIRECTORY ${MYSQL_INCLUDE_PATH})
                set(MYSQL_LIBRARIES ${MYSQL_LIB_PATH})
                set(MYSQL_INCLUDE_DIRS ${MYSQL_INCLUDE_PATH})
                set(MYSQL_FOUND TRUE)
                message(STATUS "Found MySQL manually: ${MYSQL_LIB_PATH}")
            else()
                message(WARNING "MySQL library not found at ${MYSQL_LIB_PATH}")
            endif()
        elseif(APPLE)
            find_library(MYSQL_LIBRARIES NAMES mysqlclient
                PATHS /usr/local/mysql/lib /usr/local/lib/mysql /opt/homebrew/lib
                PATH_SUFFIXES mysql)
            find_path(MYSQL_INCLUDE_DIRS NAMES mysql.h
                PATHS /usr/local/mysql/include /usr/local/include/mysql /opt/homebrew/include
                PATH_SUFFIXES mysql)
        elseif(UNIX)
            find_library(MYSQL_LIBRARIES NAMES mysqlclient mariadbclient
                PATHS /usr/lib /usr/lib/mysql /usr/local/lib /usr/local/lib/mysql
                PATH_SUFFIXES mysql)
            find_path(MYSQL_INCLUDE_DIRS NAMES mysql.h
                PATHS /usr/include /usr/include/mysql /usr/local/include /usr/local/include/mysql
                PATH_SUFFIXES mysql mariadb)
        endif()
        
        if(MYSQL_LIBRARIES AND MYSQL_INCLUDE_DIRS)
            set(MYSQL_FOUND TRUE)
            message(STATUS "Found MySQL manually: ${MYSQL_LIBRARIES}")
        else()
            message(WARNING "MySQL library not found on this system")
        endif()
    endif()
endif()

# Windows SDK Configuration
if(WIN32)
    set(WINDOWS_SDK_VERSION "10.0.22621.0" CACHE STRING "Windows SDK version")
endif()

# Target Definition
add_executable(SeaShell
    "SeaShell/global.cpp" "SeaShell/global.hpp"
    "SeaShell/seashell.cpp" "SeaShell/functions.hpp"
    "SeaShell/files/python.cpp" "SeaShell/files/python.hpp"
    "SeaShell/files/encrypt.cpp" "SeaShell/files/encrypt.hpp"
    "SeaShell/networking/clientsend.cpp" "SeaShell/networking/clientsend.hpp"
    "SeaShell/files/filesystem.cpp" "SeaShell/files/filesystem.hpp"
    "SeaShell/help.cpp" "SeaShell/help.hpp"
    "SeaShell/networking/ip.cpp" "SeaShell/networking/ip.hpp"
    "SeaShell/files/zip.cpp" "SeaShell/files/zip.hpp"
    "SeaShell/system/process.cpp" "SeaShell/system/process.hpp"
    "SeaShell/commands.hpp"
)

# Target Configuration
target_compile_features(SeaShell PRIVATE cxx_std_20)

# Compiler Options
if(MSVC)
    target_compile_options(SeaShell PRIVATE /W4 /WX)
else()
    target_compile_options(SeaShell PRIVATE -Wall -Wextra -Wpedantic -Werror)
endif()

# Platform Definitions
target_compile_definitions(SeaShell PRIVATE
    $<$<PLATFORM_ID:Windows>:WINDOWS>
    $<$<PLATFORM_ID:Linux>:LINUX>
    $<$<PLATFORM_ID:Darwin>:MACOS>
)

if(WIN32)
    target_compile_definitions(SeaShell PRIVATE WIN32_LEAN_AND_MEAN)
endif()

# Include Directories
target_include_directories(SeaShell PRIVATE "${PROJECT_ROOT}/SeaShell")

if(Python3_FOUND)
    target_include_directories(SeaShell PRIVATE ${Python3_INCLUDE_DIRS})
endif()

if(MYSQL_FOUND)
    target_include_directories(SeaShell PRIVATE ${MYSQL_INCLUDE_DIRS})
endif()

if(WIN32)
    if(DEFINED WINDOWS_SDK_VERSION)
        set(WIN_SDK_PATH "C:/Program Files (x86)/Windows Kits/10/Include/${WINDOWS_SDK_VERSION}/")
        if(IS_DIRECTORY "${WIN_SDK_PATH}")
            target_include_directories(SeaShell PRIVATE "${WIN_SDK_PATH}")
        else()
            message(WARNING "Windows SDK ${WINDOWS_SDK_VERSION} not found, attempting to find latest version")
            file(GLOB WIN_SDK_VERSIONS "C:/Program Files (x86)/Windows Kits/10/Include/*")
            if(WIN_SDK_VERSIONS)
                list(SORT WIN_SDK_VERSIONS)
                list(GET WIN_SDK_VERSIONS -1 LATEST_SDK)
                message(STATUS "Using latest Windows SDK: ${LATEST_SDK}")
                target_include_directories(SeaShell PRIVATE "${LATEST_SDK}")
            endif()
        endif()
    endif()
endif()

# Library Configuration
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

# Link Libraries
target_link_libraries(SeaShell PRIVATE
    ${POCO_LIBS}
    CURL::libcurl
    OpenSSL::SSL
    OpenSSL::Crypto
    Libssh2::libssh2
    fmt::fmt
)

if(Python3_FOUND)
    if(WIN32)
        string(REPLACE "." "" PYTHON_VERSION_NO_DOT ${Python3_VERSION})
        set(PythonLib_DEBUG "${USER_HOME}/AppData/Local/Programs/Python/Python${PYTHON_VERSION_NO_DOT}/libs/python${PYTHON_VERSION_NO_DOT}_d.lib")
        set(PythonLib_RELEASE "${USER_HOME}/AppData/Local/Programs/Python/Python${PYTHON_VERSION_NO_DOT}/libs/python${PYTHON_VERSION_NO_DOT}.lib")
        
        if(EXISTS "${PythonLib_DEBUG}" AND EXISTS "${PythonLib_RELEASE}")
            target_link_libraries(SeaShell PRIVATE 
                $<$<CONFIG:Debug>:${PythonLib_DEBUG}>
                $<$<CONFIG:Release>:${PythonLib_RELEASE}>
            )
        else()
            target_link_libraries(SeaShell PRIVATE ${Python3_LIBRARIES})
        endif()
    else()
        target_link_libraries(SeaShell PRIVATE ${Python3_LIBRARIES})
    endif()
endif()

if(MYSQL_FOUND)
    target_link_libraries(SeaShell PRIVATE ${MYSQL_LIBRARIES})
endif()

if(WIN32)
    target_link_libraries(SeaShell PRIVATE Ws2_32)
endif()

# Installation Rules
install(TARGETS SeaShell
    RUNTIME DESTINATION bin
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib
)

if(WIN32)
    install(FILES $<TARGET_FILE:SeaShell> DESTINATION bin)
elseif(UNIX)
    install(TARGETS SeaShell DESTINATION bin)
endif()

# Cross-compilation Support
if(CMAKE_CROSSCOMPILING)
    message(STATUS "Cross-compiling: Target system is ${CMAKE_SYSTEM_NAME}")
endif()

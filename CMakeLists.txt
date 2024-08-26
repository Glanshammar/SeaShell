cmake_minimum_required(VERSION 3.28)
project("SeaShell" VERSION 0.3)
set(CMAKE_CXX_STANDARD 20)
set(PROJECT_ROOT ${CMAKE_CURRENT_SOURCE_DIR})
set(CMAKE_VERBOSE_MAKEFILE ON)

option(USE_MYSQL "Use MySQL" ON)

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


set(VistaInclude "${USER_HOME}/CLionProjects/VistaFramework/Vista/include/Vista")
set(PythonInclude "${USER_HOME}/AppData/Local/Programs/Python/Python312/include")
set(PythonLibrary "${USER_HOME}/AppData/Local/Programs/Python/Python312/libs/python312.lib")
include_directories(
        ${VistaInclude}
        ${PythonInclude}
)

# vcpkg packages
find_package(CURL CONFIG REQUIRED)
find_package(FreeRDP CONFIG REQUIRED)
find_package(OpenSSL REQUIRED)
find_package(Libssh2 CONFIG REQUIRED)
find_package(SQLite3 REQUIRED)
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
        "SeaShell/color.cpp" "SeaShell/color.hpp"
        "SeaShell/help.cpp" "SeaShell/help.hpp"
        "SeaShell/networking/ip.cpp" "SeaShell/networking/ip.hpp"
        "SeaShell/networking/sql.cpp" "SeaShell/networking/sql.hpp"
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

set(VistaLib "${USER_HOME}/CLionProjects/VistaFramework/cmake-build-release/VistaFramework.lib")

target_link_libraries(SeaShell
        PUBLIC
        Ws2_32
        ${PythonLibrary}
        ${POCO_LIBS}
        ${VistaLib}
        CURL::libcurl
        freerdp
        OpenSSL::SSL
        OpenSSL::Crypto
        SQLite::SQLite3
        $<IF:$<TARGET_EXISTS:Libssh2::libssh2_shared>,Libssh2::libssh2_shared,Libssh2::libssh2_static>
)

if(USE_MYSQL)
    target_link_libraries(SeaShell
            PUBLIC
            "C:/Program Files/MySQL/MySQL Server 8.4/lib/mysqlclient.lib")
    include_directories("C:/Program Files/MySQL/MySQL Server 8.4/include")
endif()

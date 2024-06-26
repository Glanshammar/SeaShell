cmake_minimum_required(VERSION 3.28)
project("SeaShell" VERSION 0.3)
set(CMAKE_CXX_STANDARD 20)
set(PROJECT_ROOT ${CMAKE_CURRENT_SOURCE_DIR})
if(WIN32)
    set(USER_HOME $ENV{USERPROFILE})
elseif(UNIX)
    set(USER_HOME $ENV{HOME})
endif()
set(CMAKE_TOOLCHAIN_FILE "${USER_HOME}/.vcpkg-clion/vcpkg/scripts/buildsystems/vcpkg.cmake" CACHE STRING "")
link_directories("${USER_HOME}/.vcpkg-clion/vcpkg/installed/x64-windows/debug/lib")


if(NOT USER_HOME)
    message(FATAL_ERROR "Could not determine the user's home directory")
endif()

option(USE_MYSQL "Use MySQL" ON)
set(CMAKE_VERBOSE_MAKEFILE ON)


find_package(CURL CONFIG REQUIRED)
find_package(FreeRDP CONFIG REQUIRED)
find_package(OpenSSL REQUIRED)
find_package(Python REQUIRED COMPONENTS Development)
find_package(Libssh2 CONFIG REQUIRED)
find_package(SQLite3 REQUIRED)
find_package(Boost REQUIRED COMPONENTS
        atomic
        chrono
        container
        context
        coroutine
        date_time
        exception
        filesystem
        graph
        iostreams
        locale
        log
        math
        program_options
        process
        python
        random
        regex
        serialization
        system
        thread
        timer
)
find_package(Poco REQUIRED COMPONENTS
        Foundation
        Util
        Net
        XML
        JSON
        Crypto
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
        Poco::Crypto
        Poco::Zip
        Poco::MongoDB
        Poco::Redis
)


set(BOOST_LIBS
        Boost::atomic
        Boost::chrono
        Boost::container
        Boost::context
        Boost::coroutine
        Boost::date_time
        Boost::exception
        Boost::filesystem
        Boost::graph
        Boost::iostreams
        Boost::locale
        Boost::log
        Boost::math
        Boost::program_options
        Boost::process
        Boost::python
        Boost::random
        Boost::regex
        Boost::serialization
        Boost::system
        Boost::thread
        Boost::timer
)


target_link_libraries(SeaShell
        PUBLIC
        Ws2_32
        ${Python_LIBRARIES}
        ${POCO_LIBS}
        ${BOOST_LIBS}
        CURL::libcurl
        freerdp
        OpenSSL::SSL
        OpenSSL::Crypto
        SQLite::SQLite3
        $<IF:$<TARGET_EXISTS:Libssh2::libssh2_shared>,Libssh2::libssh2_shared,Libssh2::libssh2_static>
)
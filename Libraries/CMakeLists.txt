cmake_minimum_required(VERSION 3.27)
project(LibraryDownloader)

set(LIBRARY_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})
if(${CMAKE_SYSTEM_NAME} STREQUAL "Windows")
    set(COMPILER "Visual Studio 17 2022")
elseif(${CMAKE_SYSTEM_NAME} STREQUAL "Linux")
    set(COMPILER "GCC")
endif()


# By default, all libraries are downloaded and built. You have to download the database of your choice manually.
# Supported databases are: SQLite, MySQL, PostgreSQL & MongoDB.
set(GetPOCO ON)
set(GetAPR ON)
set(GetAPRUtil ON)
set(GetCURL ON)
set(GetNCurses ON)
set(GetFreeRDP ON)
set(GetSSH ON)
set(GetEXPAT ON)

set(EXPAT_URL "https://github.com/libexpat/libexpat/archive/refs/tags/R_2_6_2.zip")
set(OPENSSL_URL "https://slproweb.com/download/Win64OpenSSL-3_3_0.exe")
set(OPENSSL_ROOT "C:/Program Files/OpenSSL")

function(download_and_unzip url output_zip output_dir)
    # Download the ZIP file
    file(DOWNLOAD ${url} ${output_zip})

    # Create the output directory if it doesn't exist
    file(MAKE_DIRECTORY ${output_dir})

    # Unzip the file based on the platform
    if(CMAKE_SYSTEM_NAME STREQUAL "Windows")
        # Use PowerShell to unzip on Windows
        execute_process(
                COMMAND powershell -Command "Expand-Archive -Path ${output_zip} -DestinationPath ${output_dir} -Force"
                RESULT_VARIABLE unzip_result
        )
    else()
        # Use tar command on Unix-based systems
        execute_process(
                COMMAND ${CMAKE_COMMAND} -E tar xzf ${output_zip} --strip-components=1 -C ${output_dir}
                RESULT_VARIABLE unzip_result
        )
    endif()

    # Check if the unzip process succeeded
    if(unzip_result)
        message(FATAL_ERROR "Failed to unzip file: ${output_zip}")
    else()
        message(STATUS "Successfully unzipped file to: ${output_dir}")
        file(REMOVE ${output_zip})
    endif()
endfunction()

if(GetEXPAT)
    FetchContent_Declare(
            EXPAT
            GIT_REPOSITORY ${EXPAT_GIT}
            GIT_TAG ${EXPAT_TAG})
    message("Downloading Expat version ${EXPAT_TAG} from ${EXPAT_GIT}")
    FetchContent_Populate(EXPAT SOURCE_DIR "${LIBRARY_DIRECTORY}/Expat")
    message("Finished downloading Expat.")

    if(${CMAKE_SYSTEM_NAME} STREQUAL "Windows")
        message("Building Expat for Windows")
    elseif(${CMAKE_SYSTEM_NAME} STREQUAL "Linux")
        message("Building Expat for Linux")
    endif()
endif()

if(GetSSH)
    FetchContent_Declare(
            OpenSSL
            GIT_REPOSITORY ${OPENSSL_URL}
    )
    FetchContent_Populate(OpenSSL SOURCE_DIR "${LIBRARY_DIRECTORY}/OpenSSL")
endif()

if(GetAPR)
    FetchContent_Declare(
            APR
            GIT_REPOSITORY https://github.com/apache/apr.git
            GIT_TAG 1.7.4)
    FetchContent_MakeAvailable(APR)

    if(${CMAKE_SYSTEM_NAME} STREQUAL "Windows")
        message("Building APR for Windows")
    elseif(${CMAKE_SYSTEM_NAME} STREQUAL "Linux")
        message("Building APR for Linux")
    endif()
endif()

if (GetAPRUtil)
    if(${CMAKE_SYSTEM_NAME} STREQUAL "Windows")
        set(URL "https://dlcdn.apache.org//apr/apr-util-1.6.3-win32-src.zip")
    elseif(${CMAKE_SYSTEM_NAME} STREQUAL "Linux")
        set(URL "https://dlcdn.apache.org//apr/apr-util-1.6.3.tar.gz")
    endif()
    message("Downloading APR-Util from ${URL} for ${CMAKE_SYSTEM_NAME}, to ${LIBRARY_DIRECTORY}")
    file(DOWNLOAD ${URL} "${LIBRARY_DIRECTORY}/apr-util.zip")
    message("Finished downloading APR-Util.")
endif()

if(GetPOCO)
    FetchContent_Declare(
            Poco
            GIT_REPOSITORY https://github.com/google/googletest.git
            GIT_TAG        release-1.10.0
    )
    FetchContent_MakeAvailable(Poco)

    if(${CMAKE_SYSTEM_NAME} STREQUAL "Windows")
        message("Building Poco for Windows")
    elseif(${CMAKE_SYSTEM_NAME} STREQUAL "Linux")
        message("Building Poco for Linux")
    endif()
endif()
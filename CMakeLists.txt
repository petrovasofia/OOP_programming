cmake_minimum_required(VERSION 3.20)
project(OOP_programming)

set(CMAKE_CXX_STANDARD 17)

find_program(CLANG_TIDY clang-tidy)
if(CLANG_TIDY)
    set(CMAKE_CXX_CLANG_TIDY ${CLANG_TIDY})
endif()

include(FetchContent)
FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/refs/tags/v1.14.0.zip
        DOWNLOAD_EXTRACT_TIMESTAMP true
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

if(EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/lab0)
    add_subdirectory(lab0)
endif()

if(EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/lab1)
    add_subdirectory(lab1)
endif()
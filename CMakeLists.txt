cmake_minimum_required(VERSION 3.20)
project(OOP_programming)

set(CMAKE_CXX_STANDARD 17)

find_program(CLANG_TIDY clang-tidy)
if(CLANG_TIDY)
    set(CMAKE_CXX_CLANG_TIDY ${CLANG_TIDY})
endif()

add_executable(wordcount
        lab0/main.cpp
        lab0/FileReader.cpp
        lab0/WordSorter.cpp
        lab0/CsvWriter.cpp
)
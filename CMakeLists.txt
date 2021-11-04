cmake_minimum_required(VERSION 3.10)
project(AutoIndexer-Project)
set (EXE_NAME AutoIndexer)

set(input01 "keywords.txt")
set(input02 "WarAndPeaceBook1.txt")

# Copy data files to build dir
foreach (file IN LISTS input01 input02)
    configure_file(${file} ${file} COPYONLY)
endforeach ()

set(CMAKE_CXX_STANDARD 17)
add_executable(${EXE_NAME} src/main.cpp src/JPString.cpp test/catch.hpp test/test.cpp src/Driver.cpp)

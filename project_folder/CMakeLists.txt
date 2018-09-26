cmake_minimum_required(VERSION 3.12)
project(Mongo C CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_IGNORE_PATH ${CMAKE_BINARY_DIR}/MongoApplication)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

add_subdirectory(MongoLibrary)
add_subdirectory(GUI)
#add_subdirectory(MongoApplication)

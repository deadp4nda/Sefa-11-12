cmake_minimum_required(VERSION 3.10)
project(Mango C CXX)

set(CMAKE_BUILD_TYPE DEBUG)
set(CMAKE_CXX_STANDARD 11)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)


set(Qt5_DIR ~/Programme/Qt/5.12.0/gcc_64/lib/cmake/Qt5)


add_subdirectory(extern/lua)
add_subdirectory(extern/luasocket)
add_subdirectory(MangoLibrary)
add_subdirectory(GUI)


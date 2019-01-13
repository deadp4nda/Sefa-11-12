cmake_minimum_required(VERSION 3.10)
project(Mango C CXX)

set(CMAKE_SHARED_LIBRARY_PREFIX "")

set(CMAKE_BUILD_TYPE MINSIZEREL)
set(CMAKE_CXX_STANDARD 11)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)


if(UNIX)
	set(Qt5Widgets_DIR "/home/dp/Programme/Qt/5.12.0/gcc_64/lib/cmake/Qt5Widgets/")
	set(Qt5Gui_DIR "/home/dp/Programme/Qt/5.12.0/gcc_64/lib/cmake/Qt5Gui/")
	set(Qt5Core_DIR "/home/dp/Programme/Qt/5.12.0/gcc_64/lib/cmake/Qt5Core/")
	set(Qt5Network_DIR "/home/dp/Programme/Qt/5.12.0/gcc_64/lib/cmake/Qt5Network/")
endif()


add_subdirectory(extern/lua)
#add_subdirectory(extern/luasocket)
add_subdirectory(MangoLibrary)
add_subdirectory(GUI)


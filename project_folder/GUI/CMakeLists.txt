project(Genie_Unterstuetzende_Intelligenz C CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)

set(GUI_SRC main.cpp terminalw.cpp terminalw.h terminal.cpp terminal.h terminalinput.cpp terminalinput.h)

find_package(Qt5Core CONFIG REQUIRED)
find_package(Qt5Gui CONFIG REQUIRED)
find_package(Qt5Widgets CONFIG REQUIRED)

get_target_property(QtCore_location Qt5::Core LOCATION)
get_target_property(QtGui_location Qt5::Gui LOCATION)
get_target_property(QtWidgets_location Qt5::Widgets LOCATION)

include_directories(${CMAKE_SOURCE_DIR}/MangoLibrary)
include_directories(${CMAKE_SOURCE_DIR}/extern/lua/include)
#include_directories(${CMAKE_SOURCE_DIR}/extern/luasocket)

add_executable(GenUnIn WIN32 ${GUI_SRC} )

#set(CMAKE_EXE_LINKER_FLAGS " -static")
target_link_libraries(GenUnIn Qt5::Core Qt5::Gui Qt5::Widgets MangoLibrary)
target_link_libraries(GenUnIn lualib)
#target_link_libraries(GenUnIn core)
set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} "-static -lpthread -static-libgcc -static-libstdc++" )

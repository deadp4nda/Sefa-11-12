project(Genie_Unterstuetzende_Intelligenz C CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

set(GUI_SRC main.cpp
            achim.h
            achim.cpp)

find_package(Qt5Core CONFIG REQUIRED)
find_package(Qt5Gui CONFIG REQUIRED)
find_package(Qt5Widgets CONFIG REQUIRED)

get_target_property(QtCore_location Qt5::Core LOCATION)
get_target_property(QtGui_location Qt5::Gui LOCATION)
get_target_property(QtWidgets_location Qt5::Widgets LOCATION)

include_directories(${CMAKE_SOURCE_DIR}/MongoLibrary)


add_executable(GenUnIn ${GUI_SRC})

set(CMAKE_EXE_LINKER_FLAGS " -static")
target_link_libraries(GenUnIn Qt5::Core)
target_link_libraries(GenUnIn Qt5::Gui)
target_link_libraries(GenUnIn Qt5::Widgets)
target_link_libraries(GenUnIn MongoLibrary)
target_link_libraries(GenUnIn -static-libgcc -static-libstdc++)

install(TARGETS GenUnIn RUNTIME DESTINATION bin)

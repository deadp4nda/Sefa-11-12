project(MongoApplication C CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)

set(EXEC_SRC    main.cpp
                mainwindow.cpp
                mainwindow.h)

find_package(Qt5Core CONFIG REQUIRED)
find_package(Qt5Gui CONFIG REQUIRED)
find_package(Qt5Widgets CONFIG REQUIRED)

get_target_property(QtCore_location Qt5::Core LOCATION)
get_target_property(QtGui_location Qt5::Gui LOCATION)
get_target_property(QtWidgets_location Qt5::Widgets LOCATION)

include_directories(${CMAKE_SOURCE_DIR}/MongoLibrary)

add_executable(MongoApplication ${EXEC_SRC})

set(CMAKE_EXE_LINKER_FLAGS " -static")
target_link_libraries(MongoApplication Qt5::Core)
target_link_libraries(MongoApplication Qt5::Gui)
target_link_libraries(MongoApplication Qt5::Widgets)
target_link_libraries(MongoApplication MongoLibrary)
target_link_libraries(MongoApplication -static-libgcc -static-libstdc++)

install(TARGETS MongoApplication RUNTIME DESTINATION bin)
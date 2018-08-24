project(MongoLibrary)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)

set(LIB_SRC mongolib.h
			mongolib_global.h
			mongolib_global.cpp
			files/filehansz.cpp
			files/filehansz.h
			files/mngfilemanager.h
			files/mngfilemanager.cpp
			files/mngfileserver.h
			files/mngfileserver.cpp
			files/mngrecvfilesocket.h
			files/mngrecvfilesocket.cpp
			files/mngsendfilesocket.h
			files/mngsendfilesocket.cpp
			instructions/instructionhansz.h
			instructions/instructionhansz.cpp
			instructions/mngserver.h
			instructions/mngserver.cpp
			instructions/mngthmanager.h
			instructions/mngthmanager.cpp
			instructions/mongoconnection.h
			instructions/mongoconnection.cpp)
			
find_package(Qt5Core CONFIG REQUIRED)
find_package(Qt5Network CONFIG REQUIRED)

get_target_property(Qt5Core_location Qt5::Core LOCATION)
get_target_property(Qt5Network_location Qt5::Network LOCATION)

add_library(MongoLibrary STATIC ${LIB_SRC})

target_link_libraries(MongoLibrary Qt5::Core Qt5::Network)
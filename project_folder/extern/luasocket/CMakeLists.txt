cmake_minimum_required(VERSION 3.10)
project(luasocket)

set(LSRC	src/auxiliar.c
			src/auxiliar.h
			src/buffer.c
			src/buffer.h
			src/compat.c
			src/compat.h
			src/except.c
			src/except.h
			src/inet.c
			src/inet.h
			src/io.c
			src/io.h
			src/luasocket.c
			src/luasocket.h
			src/mime.c
			src/mime.h
			src/options.c
			src/options.h
			src/pierror.h
			src/select.c
			src/select.h
			src/socket.h
			src/tcp.c
			src/tcp.h
			src/timeout.c
			src/timeout.h
			src/udp.c
			src/udp.h
			)
			
include_directories(../lua/)
			
if(LINUX)
	set(LSRC ${LSRC}	
						src/serial.c
						src/usocket.c
						src/usocket.h
						src/unix.c
						src/unix.h
						src/unixdgram.c
						src/unixdgram.h
						src/unixstream.c
						src/unixstream.h)
	set(CMAKE_C_FLAGS "-Wall -Wshadow -Wextra -Wimplicit -O2 -ggdb3 -fvisibility=hidden")
elseif(WIN32 OR MINGW)
	set(LSRC ${LSRC}	src/wsocket.c
							src/wsocket.h)
	set(CMAKE_C_FLAGS "-Wall -O2 -fno-common -fvisibility=hidden")
else()
endif()


add_library(luasocket SHARED ${LSRC})

target_link_libraries(luasocket lualib)

if(WIN32 OR MINGW)
target_link_libraries(luasocket Ws2_32)
endif()
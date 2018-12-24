project(liblua)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(libSrc 	
		lapi.c
        lcode.c
        lctype.c
        ldebug.c
        ldo.c
        ldump.c
        lfunc.c
        lgc.c
        llex.c
        lmem.c
        lobject.c
        lopcodes.c
        lparser.c
        lstate.c
        lstring.c
        ltable.c
        ltm.c
        lundump.c
        lvm.c
        lzio.c
        lauxlib.c
        lbaselib.c
        lbitlib.c
        lcorolib.c
        ldblib.c
        liolib.c
        lmathlib.c
        loslib.c
        lstrlib.c
        ltablib.c
        lutf8lib.c
        loadlib.c
        linit.c
        )

if(UNIX AND NOT APPLE)
	set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} -DLUA_USE_POSIX -DLUA_USE_DLOPEN)
endif()
		
add_library(lualib STATIC ${libSrc})
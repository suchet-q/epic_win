cmake_minimum_required(VERSION 2.6)

project(R-Type)

include_directories(../lib)
include_directories(../includes/client)
include_directories(../includes/common)

file(
        GLOB_RECURSE
        multi_client_files
        ../sources/client/*
	../includes/client/*
)


file(
        GLOB_RECURSE
        multi_server_files
        ../sources/server/*
	../includes/server/*
)

file(
	GLOB
	common_files
	../sources/common
	../includes/common
)
	

file(
        GLOB_RECURSE
        windows_client_files
        ../includes/common/windows/*
	../sources/common/windows/*
)

file(
	GLOB_RECURSE
	linux_client_files
	../includes/common/linux/*
	../sources/common/linux/*
)

if ( CMAKE_COMPILER_IS_GNUCXX )

	
	include_directories(../includes/server)

     	add_executable(
		R-Type
		${multi_client_files}
		${common_files}
		${linux_client_files}
	) 

	add_executable(
		Server
		${multi_server_files}
		${common_files}
		${linux_client_files}
	) 

	set(CMAKE_CXX_FLAGS "-o3 -std=gnu++0x -ldl")
	set(EXECUTABLE_OUTPUT_PATH ../../bin)

	include_directories(../lib/sfml/linux/include)
	link_directories(../../lib/sfml/linux/lib)

	target_link_libraries(
		R-Type
		libsfml-audio.so
		libsfml-graphics.so
		libsfml-window.so
		libsfml-system.so
		pthread
		)

	target_link_libraries(
		Server
		pthread
		)

endif ( CMAKE_COMPILER_IS_GNUCXX )

if ( MSVC )

	add_executable(
		R-Type
		${multi_client_files}
		${common_files}
		${windows_client_files}
	)

	add_executable(
		Server
		${multi_server_files}
		${common_files}
		${windows_client_files}
	)

	include_directories(../lib/sfml/windows/include)

	if (CMAKE_BUILD_TYPE STREQUAL "Debug")
	
	target_link_libraries(
		R-Type
		../../lib/sfml/windows/lib/vc2010/sfml-audio-s-d
		../../lib/sfml/windows/lib/vc2010/sfml-graphics-s-d
		../../lib/sfml/windows/lib/vc2010/sfml-window-s-d
		../../lib/sfml/windows/lib/vc2010/sfml-system-s-d	
	)

	endif ()

	if (CMAKE_BUILD_TYPE STREQUAL "Release")

	target_link_libraries(
		R-Type
		../../lib/sfml/windows/lib/vc2010/sfml-audio-s
		../../lib/sfml/windows/lib/vc2010/sfml-graphics-s
		../../lib/sfml/windows/lib/vc2010/sfml-window-s
		../../lib/sfml/windows/lib/vc2010/sfml-system-s
	)

	endif ()

	set_target_properties(R-Type PROPERTIES RUNTIME_OUTPUT_DIRECTORY ../../bin )
    	set_target_properties(R-Type PROPERTIES RUNTIME_OUTPUT_DIRECTORY_DEBUG ../../bin )
    	set_target_properties(R-Type PROPERTIES RUNTIME_OUTPUT_DIRECTORY_RELEASE ../../bin )

	set_target_properties(Server PROPERTIES RUNTIME_OUTPUT_DIRECTORY ../../bin )
    	set_target_properties(Server PROPERTIES RUNTIME_OUTPUT_DIRECTORY_DEBUG ../../bin )
    	set_target_properties(Server PROPERTIES RUNTIME_OUTPUT_DIRECTORY_RELEASE ../../bin )

	set_target_properties(Server PROPERTIES INCLUDE_DIRECTORIES ../../includes/server )
	set_property(TARGET Server APPEND PROPERTY INCLUDE_DIRECTORIES ../../includes/common)

endif ( MSVC )



file(
	GLOB_RECURSE
	lib_alien_src
	../sources/libraries/Alien-DLL/*
	../sources/server/Ships.cpp
	../sources/server/Sinus.cpp
	../sources/server/Entities.cpp
	../includes/server/IAI.h
	../includes/server/Ships.h
	../includes/libraries/Alien-DLL/*
)

file(
	GLOB_RECURSE
	lib_dog_src
	../sources/libraries/Dog-DLL/*
	../sources/server/Ships.cpp
	../sources/server/Sinus.cpp
	../sources/server/Entities.cpp
	../includes/server/IAI.h
	../includes/server/Ships.h
	../includes/libraries/Dog-DLL/*
)

file(
	GLOB_RECURSE
	lib_drone_src
	../sources/libraries/Drone-DLL/*
	../sources/server/Ships.cpp
	../sources/server/Sinus.cpp
	../sources/server/Entities.cpp
	../includes/server/IAI.h
	../includes/server/Ships.h
	../includes/libraries/Drone-DLL/*
)

file(
	GLOB_RECURSE
	lib_jumper_src
	../sources/libraries/Jumper-DLL/*
	../sources/server/Ships.cpp
	../sources/server/Sinus.cpp
	../sources/server/Entities.cpp
	../includes/server/IAI.h
	../includes/server/Ships.h
	../includes/libraries/Jumper-DLL/*
)

file(
	GLOB_RECURSE
	lib_larve_src
	../sources/libraries/Larve-DLL/*
	../sources/server/Ships.cpp
	../sources/server/Sinus.cpp
	../sources/server/Entities.cpp
	../includes/server/IAI.h
	../includes/server/Ships.h
	../includes/libraries/Larve-DLL/*
)

file(
	GLOB_RECURSE
	lib_metroid_src
	../sources/libraries/Metroid-DLL/*
	../sources/server/Ships.cpp
	../sources/server/Sinus.cpp
	../sources/server/Entities.cpp
	../includes/server/IAI.h
	../includes/server/Ships.h
	../includes/libraries/Metroid-DLL/*
)

file(
	GLOB_RECURSE
	lib_xwing_src
	../sources/libraries/XWing-DLL/*
	../sources/server/Ships.cpp
	../sources/server/Sinus.cpp
	../sources/server/Entities.cpp
	../includes/server/IAI.h
	../includes/server/Ships.h
	../includes/libraries/XWing-DLL/*
)

add_library(
    libAlien
    SHARED
    ${lib_alien_src}
)

add_library(
    libDog
    SHARED
    ${lib_dog_src}
)

add_library(
    libDrone
    SHARED
    ${lib_drone_src}
)

add_library(
    libJumper
    SHARED
    ${lib_jumper_src}
)

add_library(
    libLarve
    SHARED
    ${lib_larve_src}
)

add_library(
    libMetroid
    SHARED
    ${lib_metroid_src}
)

add_library(
    libXwing
    SHARED
    ${lib_xwing_src}
)


if ( CMAKE_COMPILER_IS_GNUCXX )

include_directories(../includes/server)
include_directories(../includes/libraries/Alien-DLL)
include_directories(../includes/libraries/Dog-DLL)
include_directories(../includes/libraries/Drone-DLL)
include_directories(../includes/libraries/Jumper-DLL)
include_directories(../includes/libraries/Larve-DLL)
include_directories(../includes/libraries/Metroid-DLL)
include_directories(../includes/libraries/Xwing-DLL)

endif ( CMAKE_COMPILER_IS_GNUCXX )

if ( MSVC )

set_target_properties(libAlien PROPERTIES INCLUDE_DIRECTORIES ../../includes/server )
set_property(TARGET libAlien APPEND PROPERTY INCLUDE_DIRECTORIES ../../includes/libraries/Alien-DLL)
set_property(TARGET libAlien APPEND PROPERTY INCLUDE_DIRECTORIES ../../includes/common)

set_target_properties(libDog PROPERTIES INCLUDE_DIRECTORIES ../../includes/server )
set_property(TARGET libDog APPEND PROPERTY INCLUDE_DIRECTORIES ../../includes/libraries/Dog-DLL)
set_property(TARGET libDog APPEND PROPERTY INCLUDE_DIRECTORIES ../../includes/common)

set_target_properties(libDrone PROPERTIES INCLUDE_DIRECTORIES ../../includes/server )
set_property(TARGET libDrone APPEND PROPERTY INCLUDE_DIRECTORIES ../../includes/libraries/Drone-DLL)
set_property(TARGET libDrone APPEND PROPERTY INCLUDE_DIRECTORIES ../../includes/common)

set_target_properties(libJumper PROPERTIES INCLUDE_DIRECTORIES ../../includes/server )
set_property(TARGET libJumper APPEND PROPERTY INCLUDE_DIRECTORIES ../../includes/libraries/Jumper-DLL)
set_property(TARGET libJumper APPEND PROPERTY INCLUDE_DIRECTORIES ../../includes/common)

set_target_properties(libLarve PROPERTIES INCLUDE_DIRECTORIES ../../includes/server )
set_property(TARGET libLarve APPEND PROPERTY INCLUDE_DIRECTORIES ../../includes/libraries/Larve-DLL)
set_property(TARGET libLarve APPEND PROPERTY INCLUDE_DIRECTORIES ../../includes/common)

set_target_properties(libMetroid PROPERTIES INCLUDE_DIRECTORIES ../../includes/server )
set_property(TARGET libMetroid APPEND PROPERTY INCLUDE_DIRECTORIES ../../includes/libraries/Metroid-DLL)
set_property(TARGET libMetroid APPEND PROPERTY INCLUDE_DIRECTORIES ../../includes/common)

set_target_properties(libXwing PROPERTIES INCLUDE_DIRECTORIES ../../includes/server )
set_property(TARGET libXwing APPEND PROPERTY INCLUDE_DIRECTORIES ../../includes/libraries/Xwing-DLL)
set_property(TARGET libXwing APPEND PROPERTY INCLUDE_DIRECTORIES ../../includes/common)

set_target_properties(libAlien PROPERTIES RUNTIME_OUTPUT_DIRECTORY ../../bin )
set_target_properties(libAlien PROPERTIES RUNTIME_OUTPUT_DIRECTORY_DEBUG ../../bin )
set_target_properties(libAlien PROPERTIES RUNTIME_OUTPUT_DIRECTORY_RELEASE ../../bin )

set_target_properties(libDog PROPERTIES RUNTIME_OUTPUT_DIRECTORY ../../bin )
set_target_properties(libDog PROPERTIES RUNTIME_OUTPUT_DIRECTORY_DEBUG ../../bin )
set_target_properties(libDog PROPERTIES RUNTIME_OUTPUT_DIRECTORY_RELEASE ../../bin )

set_target_properties(libDrone PROPERTIES RUNTIME_OUTPUT_DIRECTORY ../../bin )
set_target_properties(libDrone PROPERTIES RUNTIME_OUTPUT_DIRECTORY_DEBUG ../../bin )
set_target_properties(libDrone PROPERTIES RUNTIME_OUTPUT_DIRECTORY_RELEASE ../../bin )

set_target_properties(libJumper PROPERTIES RUNTIME_OUTPUT_DIRECTORY ../../bin )
set_target_properties(libJumper PROPERTIES RUNTIME_OUTPUT_DIRECTORY_DEBUG ../../bin )
set_target_properties(libJumper PROPERTIES RUNTIME_OUTPUT_DIRECTORY_RELEASE ../../bin )

set_target_properties(libLarve PROPERTIES RUNTIME_OUTPUT_DIRECTORY ../../bin )
set_target_properties(libLarve PROPERTIES RUNTIME_OUTPUT_DIRECTORY_DEBUG ../../bin )
set_target_properties(libLarve PROPERTIES RUNTIME_OUTPUT_DIRECTORY_RELEASE ../../bin )

set_target_properties(libMetroid PROPERTIES RUNTIME_OUTPUT_DIRECTORY ../../bin )
set_target_properties(libMetroid PROPERTIES RUNTIME_OUTPUT_DIRECTORY_DEBUG ../../bin )
set_target_properties(libMetroid PROPERTIES RUNTIME_OUTPUT_DIRECTORY_RELEASE ../../bin )

set_target_properties(libXwing PROPERTIES RUNTIME_OUTPUT_DIRECTORY ../../bin )
set_target_properties(libXwing PROPERTIES RUNTIME_OUTPUT_DIRECTORY_DEBUG ../../bin )
set_target_properties(libXwing PROPERTIES RUNTIME_OUTPUT_DIRECTORY_RELEASE ../../bin )

endif ( MSVC )



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

	set(CMAKE_CXX_FLAGS "-o3 -std=gnu++0x -g3")
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

	set_target_properties(Server PROPERTIES INCLUDE_DIRECTORIES ../../includes/server )
	set_property(TARGET Server APPEND PROPERTY INCLUDE_DIRECTORIES ../../includes/common)

endif ( MSVC )

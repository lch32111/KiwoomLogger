cmake_minimum_required(VERSION 3.0.2)
project(Kiwoom_Logger 
	VERSION 1.0.0
	DESCRIPTION "Kiwoom Logger in C++"
	LANGUAGES CXX
	)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# For MFC..
set(CMAKE_MFC_FLAG 1)
add_definitions(-D_AFXDLL)

configure_file (
	"src/KLVersion.h.in"
	"${PROJECT_SOURCE_DIR}/include/KLVersion.h"
)

set (header_file
	include/KLVersion.h
	include/KW_Resource.h
	include/KW_Wrapper.hpp
     )

set (source_file
	src/main.cpp
	src/KW_Wrapper.cpp
    )
add_executable(logger ${source_file} ${header_file})

target_include_directories(logger PUBLIC include)

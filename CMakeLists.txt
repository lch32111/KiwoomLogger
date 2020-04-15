cmake_minimum_required(VERSION 3.0.2)
project(Kiwoom_Logger 
	VERSION 1.0.0
	DESCRIPTION "Kiwoom Logger in C++"
	LANGUAGES CXX
	)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

configure_file (
	"src/KLVersion.h.in"
	"${PROJECT_SOURCE_DIR}/include/KLVersion.h"
)

add_executable(logger src/main.cpp include/KLVersion.h)

target_include_directories(logger PUBLIC include)
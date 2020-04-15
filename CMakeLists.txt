# at least for Visual Studio 2017 Version
cmake_minimum_required(VERSION 3.7.2)

if (NOT WIN32)
message(FATAL_ERROR "You can build this project only in WIN32")
endif()

project(Kiwoom_Logger 
	VERSION 1.0.0
	LANGUAGES CXX
	)

configure_file (
	"src/KLVersion.h.in"
	"${PROJECT_SOURCE_DIR}/include/KLVersion.h"
)

set (header_file
	include/KLVersion.h
	include/KiwoomLogger.h
	include/KiwoomLoggerDlg.h
	include/stdafx.h
	include/targetver.h
     )


set (source_file
	src/stdafx.cpp
	src/KiwoomLogger.cpp
	src/KiwoomLoggerDlg.cpp
    )


set (resource_file
	res/KiwoomLogger.ico
	res/KiwoomLogger.rc2
	res/KiwoomLogger.rc
	res/resource.h
    )
source_group(KLHeader FILES "${header_file}")

source_group(KLSource FILES "${source_file}")

source_group(KLResource FILES "${resource_file}")

add_executable(KiwoomLogger WIN32 ${source_file} ${header_file} ${resource_file})


# https://stackoverflow.com/questions/47690822/possible-to-force-cmake-msvc-to-use-utf-8-encoding-for-source-files-without-a-bo
# for Korean Characters with utf-8 encoding in my sources
add_definitions(-D_AFXDLL)
add_definitions(-D_UNICODE)
add_definitions(-DUNICODE)
set(CMAKE_MFC_FLAG 1)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

target_include_directories(KiwoomLogger PUBLIC include)
target_include_directories(KiwoomLogger PUBLIC res)
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
	"src/KL/KLVersion.h.in"
	"${PROJECT_SOURCE_DIR}/include/KL/KLVersion.h"
)

set (MFC_HEADER_FILE
	include/KW_OpenAPI.hpp
	include/KiwoomLogger.hpp
	include/KiwoomLoggerDlg.hpp
	include/stdafx.h
	include/targetver.h
     )
list(APPEND TOTAL_FILE ${MFC_HEADER_FILE})

set (MFC_SOURCE_FILE
	src/stdafx.cpp
	src/KW_OpenAPI.cpp
	src/KiwoomLogger.cpp
	src/KiwoomLoggerDlg.cpp
	)
list(APPEND TOTAL_FILE ${MFC_SOURCE_FILE})

set (KL_HEADER_FILE
	include/KL/KLVersion.h
	include/KL/KLSystem.hpp
)
list(APPEND TOTAL_FILE ${KL_HEADER_FILE})

set(KL_SOURCE_FILE
	src/KL/KLSystem.cpp
)
list(APPEND TOTAL_FILE ${KL_SOURCE_FILE})

set (MFC_RESOURCE_FILE
	res/KiwoomLogger.ico
	res/KiwoomLogger.rc2
	res/KiwoomLogger.rc
	res/resource.h
    )
list(APPEND TOTAL_FILE ${MFC_RESOURCE_FILE})

set(KL_DOCUMENT
	doc/Specification.md
)
list(APPEND TOTAL_FILE ${KL_DOCUMENT})

add_executable(KiwoomLogger WIN32 ${TOTAL_FILE})
source_group("1_Headers\\MFC" FILES ${MFC_HEADER_FILE})
source_group("1_Headers\\KL" FILES ${KL_HEADER_FILE})
source_group("2_Sources\\MFC" FILES ${MFC_SOURCE_FILE})
source_group("2_Sources\\KL" FILES ${KL_SOURCE_FILE})
source_group("3_Documents" FILES ${KL_DOCUMENT})
source_group("4_Resources" FILES ${MFC_RESOURCE_FILE})

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
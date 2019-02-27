cmake_minimum_required(VERSION 3.8)

# Output dir
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/Lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/Lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/Bin)

if(NOT DEFINED CMAKE_BUILD_TYPE OR NOT CMAKE_BUILD_TYPE)
   SET(CMAKE_BUILD_TYPE Debug)
endif()
SET(CMAKE_BUILD_TYPE ${CMAKE_BUILD_TYPE} CACHE STRING "Build Debug/Release" FORCE)

# thirdpart
add_subdirectory("thirdpart")
include_directories("thirdpart")

# DuiMini
add_subdirectory("DuiMini")
add_subdirectory("Demo")	# TODO: change the folder name

# Tools
option(DUI_BUILD_TOOLS "Build tools" ON)
if(DUI_BUILD_TOOLS)
	add_subdirectory("Tools")
endif()
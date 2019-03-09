cmake_minimum_required(VERSION 3.8)

macro(override_option var default type docstring)
    if(NOT DEFINED ${var})
        set(${var} ${default})
    endif()
    set(${var} ${${var}} CACHE ${type} ${docstring} FORCE)
endmacro()

# Output dir
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY $<1:${CMAKE_BINARY_DIR}/Lib/${CMAKE_BUILD_TYPE}>)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY $<1:${CMAKE_BINARY_DIR}/Lib/${CMAKE_BUILD_TYPE}>)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY $<1:${CMAKE_BINARY_DIR}/Bin/${CMAKE_BUILD_TYPE}>)

override_option(CMAKE_BUILD_TYPE Debug STRING "Choose the type of build (Debug or Release)")
override_option(BUILD_SHARED_LIBS FALSE BOOL "Build shared libraries (DLLs)")

enable_testing()

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

# Tools
option(DUI_BUILD_TESTS "Build tests" OFF)
if(DUI_BUILD_TESTS)
	add_subdirectory("Tests")
endif()
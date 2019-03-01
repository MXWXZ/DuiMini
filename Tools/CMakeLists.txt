cmake_minimum_required(VERSION 3.8)

# we need C++11
set(CMAKE_CXX_STANDARD 11)

if(MSVC)
	add_definitions(-D_CRT_SECURE_NO_WARNINGS)
endif()

add_subdirectory("ResPacker")
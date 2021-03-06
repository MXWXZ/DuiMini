cmake_minimum_required(VERSION 3.8)

project("test_duimini")

macro(make_test name filename)
	add_executable(${name} "test_main.cpp" ${filename})
	target_link_libraries(${name} gtest gtest_main DuiMini)
    add_test(NAME ${name} COMMAND $<TARGET_FILE:${name}> WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/Bin/${CMAKE_BUILD_TYPE})
endmacro()

# we need C++11
set(CMAKE_CXX_STANDARD 11)

include_directories("SFML/include")
include_directories("../DuiMini/include")

# For static link
if(NOT BUILD_SHARED_LIBS)
	add_definitions(-DUILIB_STATIC)
endif()

if(MSVC)
	add_definitions(-D_CRT_SECURE_NO_WARNINGS)
endif()

file(COPY "TestRes" DESTINATION ${CMAKE_BINARY_DIR}/Bin/${CMAKE_BUILD_TYPE})
add_executable(HostFile "Tools/HostFile.cpp")

make_test(test_utils "Utils/test_utils.cpp")
make_test(test_resource "Core/test_resource.cpp")

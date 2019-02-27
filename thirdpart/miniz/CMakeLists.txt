project("miniz")

if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
	add_definitions(-D_FILE_OFFSET_BITS=64)
	add_definitions(-D_LARGEFILE64_SOURCE)
endif()

add_library(miniz "miniz.c")
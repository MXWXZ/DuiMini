cmake_minimum_required(VERSION 3.8)

project("DuiMini")

include(CheckFunctionExists)

# check stricmp
check_function_exists(_stricmp HAVE_STRICMP)
check_function_exists(strcasecmp HAVE_STRCASECMP)

if(NOT HAVE_STRICMP AND NOT HAVE_STRCASECMP)
    message(FATAL_ERROR "ERROR: _stricmp or strcasecmp must exist!")
endif()

configure_file(
	${CMAKE_CURRENT_SOURCE_DIR}/include/UIBuildConfig.h.in
	${CMAKE_CURRENT_SOURCE_DIR}/include/UIBuildConfig.h
)

# we need C++11
set(CMAKE_CXX_STANDARD 11)

# shared lib flag
if(BUILD_SHARED_LIBS)
	add_definitions(-DUILIB_EXPORT)
else()
	add_definitions(-DUILIB_STATIC)
endif()

if(MSVC)
	add_definitions(-D_CRT_SECURE_NO_WARNINGS)
endif()

# make SFML included
include_directories("SFML/include")

# make include more elegant
include_directories("include")

# all files
set(INCROOT ${PROJECT_SOURCE_DIR}/include)
set(SRCROOT ${PROJECT_SOURCE_DIR}/src)

set(SRC
    ${SRCROOT}/Utils/UIException.cpp
	${SRCROOT}/Utils/UIUnzip.cpp
	${SRCROOT}/Utils/UIUtils.cpp
	${INCROOT}/Utils/UIEvent.hpp
	${INCROOT}/Utils/UIXmlParse.hpp

	${SRCROOT}/Core/UISystem.cpp
	${SRCROOT}/Core/Resource/UIResFile.cpp
	${SRCROOT}/Core/Resource/UIResource.cpp
	${SRCROOT}/Core/Resource/UIResRaw.cpp
	${SRCROOT}/Core/Resource/UIResZip.cpp
	${INCROOT}/Core/Resource/UIResLoader.hpp
)

add_library(DuiMini ${SRC})

target_link_libraries(DuiMini sfml-graphics miniz)
set_target_properties(DuiMini PROPERTIES DEBUG_POSTFIX -d)	# add -d in Debug mode

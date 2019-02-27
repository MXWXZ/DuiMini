project("DuiMini")

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
aux_source_directory("include/Utils" UTILS_HPP)
aux_source_directory("include/Core/Resource" CORE_RESOURCE_HPP)
aux_source_directory("src/Utils" UTILS_SRC)
aux_source_directory("src/Core/Resource" CORE_RESOURCE_SRC)
aux_source_directory("src/Core" CORE_SRC)
LIST (APPEND ALL_SRC
	${UTILS_HPP}
	${CORE_RESOURCE_HPP}
    ${UTILS_SRC}
	${CORE_RESOURCE_SRC}
	${CORE_SRC}
)

add_library(DuiMini ${ALL_SRC})

target_link_libraries(DuiMini sfml-graphics miniz)
set_target_properties(DuiMini PROPERTIES DEBUG_POSTFIX -d)	# add -d in Debug mode

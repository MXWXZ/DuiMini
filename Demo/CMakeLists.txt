# TODO: change the project name as you wish
project("Demo")

# set VS startup project
if(MSVC)
	set_property(DIRECTORY PROPERTY VS_STARTUP_PROJECT ${PROJECT_NAME})
endif()

# Remove the console window in Release mode
if(MSVC)
	set(CMAKE_EXE_LINKER_FLAGS_RELEASE "${CMAKE_EXE_LINKER_FLAGS} /SUBSYSTEM:WINDOWS /ENTRY:mainCRTStartup")
endif()

# include DuiMini
include_directories("SFML/include")
include_directories("../DuiMini/include")

# For static link
if(NOT BUILD_SHARED_LIBS)
	add_definitions(-DUILIB_STATIC)
endif()

# TODO: Add project files
set(SRC_FILES
    "Demo.cpp"
)

# add exe
add_executable(${PROJECT_NAME} ${SRC_FILES})

# link libraries
target_link_libraries(${PROJECT_NAME} DuiMini)
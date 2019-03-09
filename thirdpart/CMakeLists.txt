cmake_minimum_required(VERSION 3.8)

add_subdirectory("miniz")
add_subdirectory("pugixml")

# SFML
override_option(SFML_BUILD_NETWORK FALSE BOOL "TRUE to build SFML's Network module.")
override_option(SFML_BUILD_AUDIO FALSE BOOL "TRUE to build SFML's Audio module.")

add_subdirectory("SFML")

# googletest
override_option(INSTALL_GTEST FALSE BOOL "Enable installation of googletest. (Projects embedding googletest may want to turn this OFF.)")
if(MSVC)
	override_option(gtest_force_shared_crt TRUE BOOL "Enable when use MSVC")
endif()
add_subdirectory("googletest")
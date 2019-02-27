macro(thirdpart_option var default)
    if(NOT DEFINED ${var})
        set(${var} ${default})
    endif()
endmacro()

add_subdirectory("miniz")

# SFML
thirdpart_option(SFML_BUILD_NETWORK FALSE)
thirdpart_option(SFML_BUILD_AUDIO FALSE)
thirdpart_option(BUILD_SHARED_LIBS FALSE)

add_subdirectory("SFML")
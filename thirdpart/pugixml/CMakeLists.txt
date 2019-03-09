project("pugixml")

add_library(pugixml STATIC "pugiconfig.hpp" "pugixml.cpp" "pugixml.hpp")
set_property(TARGET pugixml PROPERTY POSITION_INDEPENDENT_CODE ON)
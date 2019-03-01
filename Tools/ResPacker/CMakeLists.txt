cmake_minimum_required(VERSION 3.8)

project("ResPacker")

set(SRC_FILES
    "ResPacker.cpp"
)

add_executable(${PROJECT_NAME} ${SRC_FILES})
target_link_libraries(${PROJECT_NAME} miniz)
cmake_minimum_required(VERSION 3.7)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
# set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

project(Neru)

include_directories(${PROJECT_SOURCE_DIR}/src)

file(GLOB_RECURSE NERU_SRC ${PROJECT_SOURCE_DIR}/src/*.cc)
add_executable(neru ${NERU_SRC} ${PARSER_SRC})

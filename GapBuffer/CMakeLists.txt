cmake_minimum_required(VERSION 3.14)
project(GapBuffer LANGUAGES CXX)

add_library(GapBuffer INTERFACE)

file(GLOB SRCS "${CMAKE_CURRENT_SOURCE_DIR}/src/GapBuffer/*.cpp")

target_sources(GapBuffer INTERFACE
    ${SRCS}
)

target_include_directories(GapBuffer INTERFACE 
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_compile_features(GapBuffer INTERFACE cxx_std_11)
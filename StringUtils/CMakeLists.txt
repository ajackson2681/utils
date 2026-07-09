cmake_minimum_required(VERSION 3.14)
project(StringUtils LANGUAGES CXX)

add_library(StringUtils INTERFACE)

file(GLOB SRCS "${CMAKE_CURRENT_SOURCE_DIR}/src/StringUtils/*.cpp")

target_sources(StringUtils INTERFACE
    ${SRCS}
)

target_include_directories(StringUtils INTERFACE 
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_compile_features(StringUtils INTERFACE cxx_std_11)
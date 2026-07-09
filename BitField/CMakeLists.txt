cmake_minimum_required(VERSION 3.14)
project(BitField LANGUAGES CXX)

add_library(BitField INTERFACE)

target_include_directories(BitField INTERFACE 
    ${CMAKE_CURRENT_SOURCE_DIR}/include)

target_compile_features(BitField INTERFACE cxx_std_11)
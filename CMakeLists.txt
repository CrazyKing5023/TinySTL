cmake_minimum_required(VERSION 3.7)
project(TinySTL)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES test/main.cpp StlSrc/algo.h StlSrc/algobase.h StlSrc/vector.h)
add_executable(TinySTL ${SOURCE_FILES})
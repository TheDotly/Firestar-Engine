cmake_minimum_required(VERSION 3.16)
project(FirestarSDK CXX)

set(CMAKE_EXPORT_COMPILE_COMMANDS true)

set(CMAKE_CXX_STANDARD 17)

add_subdirectory("Firestar Engine")

add_subdirectory("Firestar Editor")
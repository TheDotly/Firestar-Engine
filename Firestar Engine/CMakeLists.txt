cmake_minimum_required(VERSION 3.16)

project(FirestarEngine CXX)

file(GLOB_RECURSE SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp
)

# Add the header files for FirestarEditor
file(GLOB_RECURSE HEADERS
    ${CMAKE_CURRENT_SOURCE_DIR}/include/*.h
)

set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS true)

add_library(FirestarEngine SHARED 
    ${SOURCES}
    ${HEADERS}
)

target_include_directories(FirestarEngine PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

target_compile_definitions(FirestarEngine PRIVATE FIRESTARENGINE_EXPORTS)
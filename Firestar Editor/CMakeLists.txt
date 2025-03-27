cmake_minimum_required(VERSION 3.16)

project(FirestarEditor)

set(CMAKE_CXX_STANDARD 17)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../FirestarEngine/include)

file(GLOB_RECURSE SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp
)

# Add the header files for FirestarEditor
file(GLOB_RECURSE HEADERS
    ${CMAKE_CURRENT_SOURCE_DIR}/include/*.h
)

add_executable(FirestarEditor ${SOURCES} ${HEADERS})

target_link_libraries(FirestarEditor PUBLIC FirestarEngine)

target_include_directories(FirestarEditor PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

INSTALL(TARGETS FirestarEditor DESTINATION ${CMAKE_SOURCE_DIR}/SDK)

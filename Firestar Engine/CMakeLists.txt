cmake_minimum_required(VERSION 3.16)
project(FirestarEngine CXX)

find_package(Vulkan REQUIRED)

file(GLOB_RECURSE SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp
)

# Add the header files for FirestarEditor
file(GLOB_RECURSE HEADERS
    ${CMAKE_CURRENT_SOURCE_DIR}/include/*.h
)

set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS true)

#libraries
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/Library/fmt)

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/Library/SDL)

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/Library/cpptrace)


add_library(FirestarEngine SHARED 
    ${SOURCES}
    ${HEADERS}
)

target_include_directories(FirestarEngine PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_include_directories(FirestarEngine PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/Library/SDL/include)
target_include_directories(FirestarEngine PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/Library/cpptrace/include)

target_link_libraries(FirestarEngine PRIVATE fmt::fmt)
target_link_libraries(FirestarEngine PRIVATE SDL3::SDL3)
target_link_libraries(FirestarEngine PRIVATE cpptrace::cpptrace)
target_link_libraries(FirestarEngine PRIVATE Vulkan::Vulkan)

if(WIN32)
  add_custom_command(
    TARGET FirestarEngine POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
    $<TARGET_FILE:cpptrace::cpptrace>
    $<TARGET_FILE_DIR:FirestarEngine>
  )
endif()

target_compile_definitions(FirestarEngine PRIVATE FIRESTARENGINE_EXPORTS)

INSTALL(TARGETS FirestarEngine DESTINATION ${CMAKE_SOURCE_DIR}/SDK)


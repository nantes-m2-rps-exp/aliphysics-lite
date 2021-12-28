cmake_minimum_required(VERSION 3.16 FATAL_ERROR)

project(aliphysics-lite LANGUAGES CXX)

include(CTest)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)

include(GNUInstallDirs)

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/stage/lib)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/stage/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/stage/bin)

set(BUILD_SHARED_LIBS ON)

find_package(aliroot-lite REQUIRED)
find_package(ROOT REQUIRED COMPONENTS Gpad)

add_subdirectory(corrfw)
add_subdirectory(muon)
add_subdirectory(muondep)
add_subdirectory(oadb)


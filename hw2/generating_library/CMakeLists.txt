project(io_tools)

# Exactly identical to the top level CMakeLists in homework 2
# ============================================================
cmake_minimum_required(VERSION 3.1)
set(CMAKE_CXX_STANDARD 11)
if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Release)
endif()

set(CMAKE_CXX_FLAGS "-Wall -Wextra -fPIC")
set(CMAKE_CXX_FLAGS_DEBUG "-g")
set(CMAKE_CXX_FLAGS_RELEASE "-O3")
set(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/lib)
# ============================================================


# Basic knowledge
include_directories(${PROJECT_SOURCE_DIR})
add_library(${PROJECT_NAME} SHARED io_tools.cpp)


# From https://cmake.org/cmake/help/cmake2.4docs.html
# Subsection Listfile Commands, bullet SET_TARGET_PROPERTIES
SET_TARGET_PROPERTIES(${PROJECT_NAME}
    PROPERTIES SUFFIX .so
)
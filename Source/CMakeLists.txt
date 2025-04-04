# Dactyl
cmake_minimum_required(VERSION 3.16.0)

set(CMAKE_BUILD_TYPE Debug)
#set(CMAKE_BUILD_TYPE Release)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -O0")

# Eigen
set(EIGEN_PATH      $ENV{EIGEN_PATH})
if(NOT EIGEN_PATH)
    message(FATAL_ERROR "EIGEN_PATH is not set!")
endif()
include_directories(${EIGEN_PATH})
message(STATUS "Using Eigen from: ${EIGEN_PATH}")

set(PROJECT_NAME    Dactyl)
set(PROJECT_EXE     Dactyl.Application)
set(LIB_MATH        Dactyl.Math)
set(LIB_MODEL       Dactyl.Model)
set(LIBS_TYPE       STATIC)

project(${PROJECT_NAME})

add_subdirectory(${LIB_MATH})
add_subdirectory(${LIB_MODEL})
add_subdirectory(${PROJECT_EXE})
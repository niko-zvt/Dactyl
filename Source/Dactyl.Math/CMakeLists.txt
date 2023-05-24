# Dactyl.Math
cmake_minimum_required(VERSION 3.16.0)

file(GLOB_RECURSE HEADER_FILES  ${PROJECT_SOURCE_DIR}/${LIB_MATH}/Internal/Include/*.h
                                ${PROJECT_SOURCE_DIR}/${LIB_MATH}/External/eigen3/Eigen/*/*.h
                                ${PROJECT_SOURCE_DIR}/${LIB_MATH}/External/eigen3/Eigen/*.h)

file(GLOB_RECURSE SOURCE_FILES ${PROJECT_SOURCE_DIR}/${LIB_MATH}/Internal/Source/*.cpp 
                               ${PROJECT_SOURCE_DIR}/${LIB_MATH}/Internal/Source/*.h)

add_library(${LIB_MATH} ${LIBS_TYPE} ${HEADER_FILES} ${SOURCE_FILES} )

target_include_directories(${LIB_MATH} 
    PUBLIC 
        ${PROJECT_SOURCE_DIR}/${LIB_MATH}/Internal/Include/
        ${PROJECT_SOURCE_DIR}/${LIB_MATH}/External/eigen3/Eigen/
)

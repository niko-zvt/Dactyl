# Dactyl.Math
cmake_minimum_required(VERSION 3.16.0)

file(GLOB_RECURSE HEADER_FILES  ${PROJECT_SOURCE_DIR}/${LIB_MATH}/Include/*.h)

file(GLOB_RECURSE SOURCE_FILES ${PROJECT_SOURCE_DIR}/${LIB_MATH}/Source/*.cpp)

add_library(${LIB_MATH} ${LIBS_TYPE} ${HEADER_FILES} ${SOURCE_FILES} )

target_include_directories(${LIB_MATH} 
    PUBLIC 
        ${PROJECT_SOURCE_DIR}/${LIB_MATH}/Include/
        ${EIGEN_PATH}/
)

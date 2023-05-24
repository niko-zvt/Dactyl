# Dactyl.Model
cmake_minimum_required(VERSION 3.16.0)

file(GLOB_RECURSE HEADER_FILES ${PROJECT_SOURCE_DIR}/${LIB_MODEL}/Include/*.h)
file(GLOB_RECURSE SOURCE_FILES ${PROJECT_SOURCE_DIR}/${LIB_MODEL}/Source/*.cpp 
                               ${PROJECT_SOURCE_DIR}/${LIB_MODEL}/Source/*.h)

add_library(${LIB_MODEL} ${LIBS_TYPE} ${HEADER_FILES} ${SOURCE_FILES})

target_link_libraries(${LIB_MODEL} ${LIB_MATH})

target_include_directories(${LIB_MODEL} 
    PUBLIC 
        ${PROJECT_SOURCE_DIR}/${LIB_MATH}/Internal/Include/
        ${PROJECT_SOURCE_DIR}/${LIB_MODEL}/Include/
)
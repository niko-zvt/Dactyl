# Dactyl.Application
cmake_minimum_required(VERSION 3.16.0)

set(Dactyl.Application_VERSION_MAJOR 1)
set(Dactyl.Application_VERSION_MINOR 0)
set(Dactyl.Application_VERSION_PATCH 0)
set(Dactyl.Application_VERSION_TWEAK 0)
set(Dactyl.Application_VERSION "${Dactyl.Application_VERSION_MAJOR}.${Dactyl.Application_VERSION_MINOR}.${Dactyl.Application_VERSION_PATCH}.${Dactyl.Application_VERSION_TWEAK}")

configure_file(
    "${PROJECT_SOURCE_DIR}/${PROJECT_EXE}/Include/ver.h.in"
    "${PROJECT_BINARY_DIR}/${PROJECT_EXE}/Include/Dactyl.Version.h"
)

configure_file(
    "${PROJECT_SOURCE_DIR}/${PROJECT_EXE}/Include/Dactyl.Utils.h"
    "${PROJECT_BINARY_DIR}/${PROJECT_EXE}/Include/Dactyl.Utils.h"
)

configure_file(
    "${PROJECT_SOURCE_DIR}/${PROJECT_EXE}/Include/Parsers/Dactyl.KChunk.h"
    "${PROJECT_BINARY_DIR}/${PROJECT_EXE}/Include/Dactyl.KChunk.h"
)

configure_file(
    "${PROJECT_SOURCE_DIR}/${PROJECT_EXE}/Include/Parsers/Dactyl.KLine.h"
    "${PROJECT_BINARY_DIR}/${PROJECT_EXE}/Include/Dactyl.KLine.h"
)

configure_file(
    "${PROJECT_SOURCE_DIR}/${PROJECT_EXE}/Include/Parsers/Dactyl.FileParser.h"
    "${PROJECT_BINARY_DIR}/${PROJECT_EXE}/Include/Dactyl.FileParser.h"
)

configure_file(
    "${PROJECT_SOURCE_DIR}/${PROJECT_EXE}/Include/Parsers/Dactyl.KChunkParser.h"
    "${PROJECT_BINARY_DIR}/${PROJECT_EXE}/Include/Dactyl.KChunkParser.h"
)

configure_file(
    "${PROJECT_SOURCE_DIR}/${PROJECT_EXE}/Include/Parsers/Dactyl.KResult.h"
    "${PROJECT_BINARY_DIR}/${PROJECT_EXE}/Include/Dactyl.KResult.h"
)

set(PROJECT_SOURCE_RESOURCES_DIR ${PROJECT_SOURCE_DIR}/${PROJECT_EXE}/Resources)

file(COPY ${PROJECT_SOURCE_RESOURCES_DIR} DESTINATION ${PROJECT_BINARY_DIR}/${PROJECT_EXE}/)

file(GLOB_RECURSE HEADER_FILES ${PROJECT_SOURCE_DIR}/${PROJECT_EXE}/Include/*.h
                               ${PROJECT_SOURCE_DIR}/${PROJECT_EXE}/Include/Parsers/*.h)
file(GLOB_RECURSE SOURCE_FILES ${PROJECT_SOURCE_DIR}/${PROJECT_EXE}/Source/*.cpp 
                               ${PROJECT_SOURCE_DIR}/${PROJECT_EXE}/Source/*.h)

add_executable(${PROJECT_EXE} ${HEADER_FILES} ${SOURCE_FILES})

target_link_libraries(${PROJECT_EXE} ${LIB_MODEL})

link_directories(${LIB_MODEL})

target_include_directories(${PROJECT_EXE} 
    PUBLIC 
        ${PROJECT_BINARY_DIR}/${PROJECT_EXE}/Include/
        ${PROJECT_BINARY_DIR}/${PROJECT_EXE}/Include/Parsers/
        ${PROJECT_BINARY_DIR}/${LIB_MATH}/Internal/Include/
        ${PROJECT_BINARY_DIR}/${LIB_MODEL}/Include/
)
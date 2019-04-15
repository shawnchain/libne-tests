cmake_minimum_required(VERSION 2.8)

ADD_DEFINITIONS( -Os -Wall -g3 -Wno-sign-compare )

PROJECT(libne-tests)

FIND_PATH(libne_include_dir NE10.h)
FIND_LIBRARY(libne NAMES NE10)

INCLUDE_DIRECTORIES(include)
INCLUDE_DIRECTORIES(${libne_include_dir})

file(GLOB_RECURSE SOURCES_C *.c)

ADD_EXECUTABLE(libne-tests ${SOURCES_C})
TARGET_LINK_LIBRARIES(libne-tests libne m)
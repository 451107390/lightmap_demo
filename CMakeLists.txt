#cmake version
cmake_minimum_required(VERSION 3.2)

#project name 
PROJECT(lightmap_demo)

SET(CMAKE_BUILD_TYPE Release)

INCLUDE_DIRECTORIES(ext)
LINK_DIRECTORIES(lib)
LINK_LIBRARIES(assimp-vc120-mt.lib freeglut.lib glew32.lib)

ADD_SUBDIRECTORY(src)



cmake_minimum_required(VERSION 3.0)

project(Imaker)

add_definitions(-std=c++11)

set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/CMake)

set( CMAKE_EXPORT_COMPILE_COMMANDS ON )

#find_package(SDL REQUIRED)
find_package(SDL2 REQUIRED)
find_package(OpenGL REQUIRED)
find_package(GLEW REQUIRED)

include_directories(${SDL2_INCLUDE_DIRS})

# Pour gérer un bug a la fac, a supprimer sur machine perso:
#set(OPENGL_LIBRARIES /usr/lib/x86_64-linux-gnu/libGL.so.1)

include_directories(${SDL2_INCLUDE_DIRS} ${OPENGL_INCLUDE_DIR} ${GLEW_INCLUDE_DIRS})
include_directories(third-party/include/imgui glimac/include class/include  third-party/include )


#Librairies
add_subdirectory(third-party/include/imgui)
add_subdirectory(glimac)
add_subdirectory(class)

set(ALL_LIBRARIES glimac imgui class ${SDL2_LIBRARIES} ${OPENGL_LIBRARIES} ${GLEW_LIBRARY})

#file(GLOB UP_DIRECTORY "UP*")

add_subdirectory(UP)


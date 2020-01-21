cmake_minimum_required(VERSION 3.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "-Wall -Wconversion -ggdb")

#Enable debug symbols
if (NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Debug CACHE STRING "Choose debug or release" FORCE)
endif()

project(game)

#Add the files
file(GLOB_RECURSE SOURCES src/*.cpp)
add_executable(game ${SOURCES})

#Add libraries
#SFML
set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake_modules" ${CMAKE_MODULE_PATH})
find_package(SFML REQUIRED graphics system)

#OPENGL
find_package(OpenGL REQUIRED)
if(NOT OPENGL_FOUND)
    message("ERROR: OpenGL not found")
endif(NOT OPENGL_FOUND)
set(GL_LIBRARY GL GLEW X11)

#Threads
find_package(Threads)

target_link_libraries(game Threads::Threads ${EXECUTABLE_NAME} ${SFML_LIBRARIES} ${GL_LIBRARY} glfw) 

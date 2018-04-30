#
# Specify minimum CMake version and project name
#
cmake_minimum_required (VERSION 3.0)
project (libby-city)

#
# CMake setup
#
set_property(GLOBAL PROPERTY USE_FOLDERS ON)
set (CMAKE_VERBOSE_MAKEFILE 0) # 1 should be used for debugging
set (CMAKE_SUPPRESS_REGENERATION TRUE) # Suppresses ZERO_CHECK
if(MSVC)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W4")
else()
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Wpedantic -Wnarrowing -std=c++11")
endif()

set(FREEGLUT_SOURCE_DIR "libby-city/vendor/FreeGLUT/freeglut/freeglut")

find_package(GLEW REQUIRED)
if (GLEW_FOUND)
    include_directories(${GLEW_INCLUDE_DIRS})
    link_libraries(${GLEW_LIBRARIES})
endif()

find_package(OpenGL REQUIRED)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/Modules")

find_package(GLUI REQUIRED)
include_directories(${GLUI_INCLUDE_DIRS})
set(LIBS ${LIBS} ${GLUI_LIBRARIES})

#
# Set include paths
#
include_directories (libby-city/src/
                     ${FREEGLUT_SOURCE_DIR}/include/
                     ${GLEW_SOURCE_DIR}
                     ${OPENGL_INCLUDE_DIR})

file (GLOB_RECURSE PROJECT_HEADERS libby-city/src/*.hpp
                                   libby-city/src/*.h)
file (GLOB_RECURSE PROJECT_SOURCES libby-city/src/*.cpp
                                   libby-city/src/*.cxx
                                   libby-city/src/*.cc
                                   libby-city/src/*.c)
file (GLOB         PROJECT_CONFIGS CMakeLists.txt
                                  .gitignore
                                  .gitmodules)

#
# Organizing files
#
source_group ("headers" FILES ${PROJECT_HEADERS})
source_group ("sources" FILES ${PROJECT_SOURCES})
source_group ("vendors" FILES ${VENDORS_SOURCES})

#
# Set executable and target link libraries
#
add_definitions (#-DGLFW_INCLUDE_NONE
                 -DPROJECT_SOURCE_DIR=\"${PROJECT_SOURCE_DIR}\")
add_executable (
    ${PROJECT_NAME}
    ${PROJECT_SOURCES}
    ${PROJECT_HEADERS}
    ${PROJECT_CONFIGS}
    ${VENDORS_SOURCES})

target_link_libraries (${PROJECT_NAME}
                       ${GLUI_LIBRARY}
                       ${GLEW_LIBRARIES}
                       ${GLUT_LIBRARY}
                       ${OPENGL_LIBRARIES})

set_target_properties (${PROJECT_NAME} PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/${PROJECT_NAME})

cmake_minimum_required (VERSION 3.1)

# cmake_policy(PUSH)
# cmake_policy(POP)
# cmake_policy(SET CMP0048 OLD)
project (kalsengi)
#set(PROJECT_VERSION_MAJOR "1")
#set(PROJECT_VERSION_MINOR "0")

## third party libraries
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
# option(GLFW_BUILD_DOCS OFF)
# option(GLFW_BUILD_EXAMPLES OFF)
# option(GLFW_BUILD_TESTS OFF)
add_subdirectory(thirdParty/glfw)
include_directories (thirdParty/glfw/include)

## glad
include_directories (thirdParty/glad/include)
set (THIRD_PARTY_SOURCES ${THIRD_PARTY_SOURCES} thirdParty/glad/src/glad.c)
if (${CMAKE_CXX_COMPILER_ID} STREQUAL "GNU" AND NOT WIN32)
    set (GLAD_LIBRARY_DEPENDENCIES dl)
endif ()
## end glad

## glm
include_directories (thirdParty/glm)
## end glm

## imgui
include_directories (thirdParty/imgui)
set (THIRD_PARTY_SOURCES ${THIRD_PARTY_SOURCES}
    thirdParty/imgui/imgui.cpp
    thirdParty/imgui/imgui_draw.cpp)
    #thirdParty/imgui/examples/opengl3_example/imgui_impl_glfw_gl3.cpp)
## end imgui

## boost
find_package(Boost)
if (Boost_FOUND)
    include_directories(${Boost_INCLUDE_DIRS})
else ()
    message (WARNING "Boost was not found. Please download and install it.")
endif ()
## end boost

## assimp
# option(ASSIMP_BUILD_ASSIMP_TOOLS "If the supplementary tools for Assimp are built in addition to the library." OFF)
# option(ASSIMP_BUILD_SAMPLES "If the official samples are built as well (needs Glut)." OFF)
# option(ASSIMP_BUILD_TESTS "If the test suite for Assimp is built in addition to the library." OFF)
set(ASSIMP_BUILD_ASSIMP_TOOLS OFF CACHE BOOL "" FORCE)
set(ASSIMP_BUILD_SAMPLES OFF CACHE BOOL "" FORCE)
set(ASSIMP_BUILD_TESTS OFF CACHE BOOL "" FORCE)
add_subdirectory(thirdParty/assimp)
include_directories (thirdParty/assimp/include)
## end assimp

## stb image loader
include_directories (thirdParty/stb)
## end std


## set compiler flags
set (CMAKE_CXX_STANDARD 11)
set (CXX_STANDARD_REQUIRED ON)
# set (CMAKE_CXX_EXTENSIONS OFF)

if (${CMAKE_CXX_COMPILER_ID} STREQUAL "GNU" OR ${CMAKE_CXX_COMPILER_ID} STREQUAL "Clang")
    # set (warnings "-Wall -Wextra -Wpedantic -Werror")
    # set (warnings "-Wall -Wextra")  # had to turn off pedantic in order to compile glad
    set (warnings "-Wall -Wextra -Werror")  # had to turn off pedantic in order to compile glad
elseif (${CMAKE_CXX_COMPILER_ID} STREQUAL "MSVC") #if (MSVC)
    set (warnings "/W4 /WX /EHsc")
endif()

set (CMAKE_C_FLAGS ${CMAKE_C_FLAGS} ${warnings})
set (CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} ${warnings})

# if (NOT configuredOnce)
#     set (CMAKE_C_FLAGS ${warnings} CACHE STRING "flags used by the compiler during all build types." FORCE)
#     set (CMAKE_CXX_FLAGS ${warnings} CACHE STRING "flags used by the compiler during all build types." FORCE)
# endif ()
## end compiler flags


## own project
include_directories (include)
set (PROJECT_SOURCES src/main.cpp
                     src/window.cpp
                     src/logger.cpp
                     src/shader.cpp
                     src/camera.cpp
                     src/time.cpp
                     src/mesh.cpp
                     src/model.cpp
                     src/quad.cpp
                     src/imgui_impl_glfw_gl3.cpp)
set (PROJECT_LIBRARIES glfw assimp)

add_executable (${PROJECT_NAME} ${PROJECT_SOURCES}
                                ${THIRD_PARTY_SOURCES})

target_link_libraries (${PROJECT_NAME} ${PROJECT_LIBRARIES}
                                       ${GLAD_LIBRARY_DEPENDENCIES})

enable_testing ()
add_test (kalsengiTest ${PROJECT_NAME}) # add_test (testName target)

# set (configuredOnce TRUE CACHE INTERNAL "a flag showing that CMake has configured at least once.")

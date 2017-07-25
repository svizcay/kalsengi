cmake_minimum_required (VERSION 3.1)
project (kalsengi VERSION 1.0)

## third party libraries
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
add_subdirectory(thirdParty/glfw-3.2.1)
include_directories (thirdParty/glfw-3.2.1/include)

## glad
include_directories (thirdParty/glad/include)
set (THIRD_PARTY_SOURCES ${THIRD_PARTY_SOURCES} thirdParty/glad/src/glad.c)
if (${CMAKE_CXX_COMPILER_ID} STREQUAL "GNU" AND NOT WIN32)
    set (GLAD_LIBRARY_DEPENDENCIES dl)
endif ()
## end glad

## glm
include_directories (thirdParty/glm-0.9.8.4)
## end glm

## imgui
include_directories (thirdParty/imgui-1.50)
set (THIRD_PARTY_SOURCES ${THIRD_PARTY_SOURCES}
    thirdParty/imgui-1.50/imgui.cpp
    thirdParty/imgui-1.50/imgui_draw.cpp
    thirdParty/imgui-1.50/imgui_impl_glfw_gl3.cpp)
## end imgui

## set compiler flags
set (CMAKE_CXX_STANDARD 11)
set (CXX_STANDARD_REQUIRED ON)
# set (CMAKE_CXX_EXTENSIONS OFF)

if (${CMAKE_CXX_COMPILER_ID} STREQUAL "GNU" OR ${CMAKE_CXX_COMPILER_ID} STREQUAL "Clang")
    # set (warnings "-Wall -Wextra -Wpedantic -Werror")
    set (warnings "-Wall -Wextra -Werror")  # had to turn off pedantic in order to compile glad
elseif (${CMAKE_CXX_COMPILER_ID} STREQUAL "MSVC")
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
                     src/time.cpp)
set (PROJECT_LIBRARIES glfw)

add_executable (${PROJECT_NAME} ${PROJECT_SOURCES}
                                ${THIRD_PARTY_SOURCES})

target_link_libraries (${PROJECT_NAME} ${PROJECT_LIBRARIES}
                                       ${GLAD_LIBRARY_DEPENDENCIES})

enable_testing ()
add_test (kalsengiTest ${PROJECT_NAME}) # add_test (testName target)

# set (configuredOnce TRUE CACHE INTERNAL "a flag showing that CMake has configured at least once.")

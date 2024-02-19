cmake_minimum_required(VERSION 3.17)

project(Test)

include_directories(../deps/glfw/glfw-3.3.8)
include_directories(../deps/glad/include)
include_directories(../deps/glfw/glfw-3.3.8/include)
include_directories(../deps/glfw/glfw-3.3.8/deps)

set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

add_executable(main main.cpp ../deps/glad/src/glad.c Sphere.cpp)

add_subdirectory(../deps/glfw/glfw-3.3.8 ./lib)

target_link_libraries(main glfw)

cmake_minimum_required(VERSION 3.10.0)
project(opengl-tutorial CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)


if (WIN32)
    # include_directories($ENV{GLM_ROOT})
    include_directories($ENV{GLFW_ROOT}\\include)
    include_directories($ENV{GLEW_ROOT}\\include)
    # message(STATUS "Using GLM: $ENV{GLM_ROOT} ")
    message(STATUS "Using GLFW: $ENV{GLFW_ROOT} ")

elseif (LINUX)

endif (WIN32)

add_subdirectory(src)
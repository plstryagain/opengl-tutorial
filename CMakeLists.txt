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

include_directories(vendor)
include_directories(src)
add_subdirectory(vendor/stb_image)
add_subdirectory(vendor/imgui)
add_subdirectory(src)
add_subdirectory(src/tests)

add_executable(
    ${PROJECT_NAME}
    $<TARGET_OBJECTS:main_obj>
    $<TARGET_OBJECTS:stb_image_obj>
    $<TARGET_OBJECTS:imgui_obj>
    $<TARGET_OBJECTS:tests_obj>
)

if (WIN32)
    # add_custom_command(TARGET ${PROJECT_NAME} PRE_BUILD
    #     COMMAND ${CMAKE_SOURCE_DIR}/shaders/compile_win.bat
    # )
    target_link_directories(${PROJECT_NAME} PUBLIC "$ENV{GLFW_ROOT}/lib-vc2022" "$ENV{GLEW_ROOT}/lib/Release/x64")
    target_link_libraries(${PROJECT_NAME} PUBLIC glfw3.lib -lopengl32 glew32s.lib)
elseif (LINUX)
    # add_custom_command(TARGET ${PROJECT_NAME} PRE_BUILD
    #     COMMAND ${CMAKE_SOURCE_DIR}/shaders/compile_linux.sh
    # )
    target_link_libraries(${PROJECT_NAME} PUBLIC -l:libGLEW.a glfw GL)
endif ()
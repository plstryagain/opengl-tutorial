add_executable(${PROJECT_NAME} main.cpp renderer.cpp vertex_buffer.cpp index_buffer.cpp vertex_array.cpp shader.cpp)

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
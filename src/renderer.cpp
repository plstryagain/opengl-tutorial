#include "renderer.h"

#include <iostream>

void gl_clear_error()
{
    while (glGetError() != GL_NO_ERROR){

    }
}

bool gl_log_call(std::string_view function, std::string_view file, int32_t line)
{
    while (GLenum error = glGetError()) {
        std::cout << "[OpenGL error] (" << error << "): " << function <<
        " " << file << " " << line << std::endl;
        return false;
    }
    return true;
}
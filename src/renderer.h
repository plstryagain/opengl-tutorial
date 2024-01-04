#pragma once

#define GLEW_STATIC
#include <GL/glew.h>

#include <string>

#ifdef _MSC_VER
#define ASSERT(x) if (!(x)) __debugbreak();
#else
#define ASSERT(x) if (!(x)) __builtin_trap();
#endif

#define GLCall(x) gl_clear_error();\
    x;\
    ASSERT(gl_log_call(#x, __FILE__, __LINE__))


void gl_clear_error();

bool gl_log_call(std::string_view function, std::string_view file, int32_t line);
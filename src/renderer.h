#pragma once

#define GLEW_STATIC
#include <GL/glew.h>

#include <string>

#include "vertex_array.h"
#include "index_buffer.h"
#include "shader.h"

class Renderer
{
public:
    void Draw(const VertexArray& va, const IndexBuffer& ib, const Shader& shader) const;
    void Clear() const;
};
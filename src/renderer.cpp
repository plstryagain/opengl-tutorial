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

void Renderer::Draw(const VertexArray& va, const IndexBuffer& ib, const Shader& shader) const
{
    shader.Bind();
    // shader.SetUnifrom4f("u_Color", r, 0.3f, 0.8f, 1.0f);

    va.Bind();
    ib.Bind();
    GLCall(glDrawElements(GL_TRIANGLES, ib.GetCount(), GL_UNSIGNED_INT, nullptr));

}

void Renderer::Clear() const
{
    glClear(GL_COLOR_BUFFER_BIT);
}
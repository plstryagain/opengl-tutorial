#include "renderer.h"
#include "gl_error.h"

#include <iostream>

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
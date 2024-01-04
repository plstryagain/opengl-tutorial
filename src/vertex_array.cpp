#include "vertex_array.h"
#include "renderer.h"

VertexArray::VertexArray()
{
    glGenVertexArrays(1, &renderer_id_);
}

VertexArray::~VertexArray()
{
    glDeleteVertexArrays(1, &renderer_id_);
}

void VertexArray::AddBuffer(const VertexBuffer& vb, const VertexBufferLayout& layout)
{
    Bind();
    vb.Bind();
    const auto& elements = layout.GetElements();
    int32_t i = 0;
    uint32_t offset = 0;
    for (const auto& element : elements) {
        glEnableVertexAttribArray(i);
        glVertexAttribPointer(i, element.count, element.type, element.is_normalized, layout.GetStride(), reinterpret_cast<const void*>(offset));
        offset += element.count * VertexBufferElement::GetSizeOfType(element.type);
        ++i;
    }

}

void VertexArray::Bind() const
{
    glBindVertexArray(renderer_id_);
}

void VertexArray::Unbind() const
{
    glBindVertexArray(0);
}
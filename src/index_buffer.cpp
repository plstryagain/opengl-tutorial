#include "index_buffer.h"
#include "renderer.h"

IndexBuffer::IndexBuffer(const uint32_t* data, uint32_t count)
    : count_(count)
{
    ASSERT(sizeof(uint32_t) == sizeof(GLuint));
    glGenBuffers(1, &renderer_id_);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, renderer_id_);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(uint32_t), data, GL_STATIC_DRAW);

}

IndexBuffer::~IndexBuffer()
{
    glDeleteBuffers(1, &renderer_id_);
}


void IndexBuffer::Bind() const
{
    glBindBuffer(GL_ARRAY_BUFFER, renderer_id_);
}

void IndexBuffer::Unbind() const
{
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

uint32_t IndexBuffer::GetCount() const
{
    return count_;
}
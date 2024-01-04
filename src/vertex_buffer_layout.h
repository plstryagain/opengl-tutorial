#pragma once

#include <vector>
#include <GL/glew.h>

struct VertexBufferElement
{
    uint32_t type;
    uint32_t count;
    unsigned char is_normalized;

    static uint32_t GetSizeOfType(uint32_t type)
    {
        switch (type) {
            case GL_FLOAT:          return sizeof(GLfloat);
            case GL_UNSIGNED_INT:   return sizeof(GLuint);
            case GL_UNSIGNED_BYTE:  return sizeof(GLubyte);
            default:
                return 0;
        }
    }
};

class VertexBufferLayout
{
public:
    VertexBufferLayout()
        : stride_(0)
    {

    }
    
    ~VertexBufferLayout() {}

    template<typename T>
    void Push(uint32_t count)
    {
        static_assert(false);
    }

    template<>
    void Push<float>(uint32_t count)
    {
        elements_.push_back({
            .type = GL_FLOAT,
            .count = count,
            .is_normalized = GL_FALSE
        });
        stride_ += VertexBufferElement::GetSizeOfType(GL_FLOAT) * count;
    }

    template<>
    void Push<uint32_t>(uint32_t count)
    {
        elements_.push_back({
            .type = GL_UNSIGNED_INT,
            .count = count,
            .is_normalized = GL_FALSE
        });
        stride_ += VertexBufferElement::GetSizeOfType(GL_UNSIGNED_INT) * count;
    }

    template<>
    void Push<unsigned char>(uint32_t count)
    {
        elements_.push_back({
            .type = GL_UNSIGNED_BYTE,
            .count = count,
            .is_normalized = GL_TRUE
        });
        stride_ += VertexBufferElement::GetSizeOfType(GL_UNSIGNED_BYTE) * count;
    }

    inline const std::vector<VertexBufferElement> GetElements() const { return elements_; }
    inline uint32_t GetStride() const { return stride_; }

private:
    std::vector<VertexBufferElement> elements_;
    uint32_t stride_;
};
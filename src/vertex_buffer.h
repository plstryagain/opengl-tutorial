#pragma once

#include <cstdint>
#include <vector>

class VertexBuffer
{
public:
    VertexBuffer(const void* data, uint32_t size);
    // VertexBuffer(const std::vector<unsigned char>& data);
    ~VertexBuffer();

    void Bind() const;
    void Unbind() const;

private:
    uint32_t renderer_id_;
};
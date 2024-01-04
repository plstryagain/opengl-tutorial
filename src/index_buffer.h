#pragma once

#include <cstdint>
#include <vector>

class IndexBuffer
{
public:
    IndexBuffer(const uint32_t* data, uint32_t count);
    // IndexBuffer(const std::vector<unsigned char>& data);
    ~IndexBuffer();

    void Bind() const;
    void Unbind() const;
    uint32_t GetCount() const;

private:
    uint32_t renderer_id_;
    uint32_t count_;
};
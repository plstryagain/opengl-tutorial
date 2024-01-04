#pragma once

#include "renderer.h"
#include <string>

class Texture
{
public:
    Texture(std::string_view file_path);
    ~Texture();

    void Bind(uint32_t slot = 0) const;
    void Unbind() const;

    inline int32_t GetWidth() const { return width_; }
    inline int32_t GetHeight() const { return height_; }

private:
    uint32_t renderer_id_;
    std::string file_path_;
    unsigned char* local_buffer_;
    int32_t width_;
    int32_t height_;
    int32_t bits_per_pixel_;
};
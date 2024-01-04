#include "texture.h"
#include "gl_error.h"

#include <stb_image/stb_image.h>

Texture::Texture(std::string_view file_path)
    : renderer_id_(0), file_path_(file_path), local_buffer_(nullptr), width_(0), height_(0), bits_per_pixel_(0)

{
    stbi_set_flip_vertically_on_load(1);
    local_buffer_ = stbi_load(file_path.data(), &width_, &height_, &bits_per_pixel_, 4);

    GLCall(glGenTextures(1, &renderer_id_));
    GLCall(glBindTexture(GL_TEXTURE_2D, renderer_id_));

    GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
    GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
    GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE));
    GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE));

    GLCall(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width_, height_, 0, GL_RGBA, GL_UNSIGNED_BYTE, local_buffer_));
    GLCall(glBindTexture(GL_TEXTURE_2D, 0));

    if (local_buffer_) {
        stbi_image_free(local_buffer_);
    }
}

Texture::~Texture()
{
    glDeleteTextures(1, &renderer_id_);
}

void Texture::Bind(uint32_t slot) const
{
    GLCall(glActiveTexture(GL_TEXTURE0 + slot));
    GLCall(glBindTexture(GL_TEXTURE_2D, renderer_id_));
}

void Texture::Unbind() const
{
    glBindTexture(GL_TEXTURE_2D, 0);
}

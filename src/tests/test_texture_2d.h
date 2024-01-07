#pragma once

#include "test.h"
#include "vertex_array.h"
#include "vertex_buffer.h"
#include "vertex_buffer_layout.h"
#include "texture.h"

#include <glm/glm.hpp>

#include <memory>

namespace test {

class TestTexture2D : public Test
{
public:
    TestTexture2D();
    ~TestTexture2D();

    void OnUpdate(float delta_time) override;
    void OnRender() override;
    void OnImGuiRender() override;

private:
    std::unique_ptr<VertexArray> vao_;
    std::unique_ptr<IndexBuffer> ibo_;
    std::unique_ptr<Shader> shader_; 
    std::unique_ptr<Texture> texture_;
    std::unique_ptr<VertexBuffer> vbo_; 
    std::unique_ptr<VertexBufferLayout> layout_;
    glm::vec3 translationA_;
    glm::vec3 translationB_;
    glm::mat4 proj_;
    glm::mat4 view_;
};

} // test
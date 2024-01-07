#include "test_texture_2d.h"
#include "glm/ext/matrix_transform.hpp"
#include "index_buffer.h"
#include "renderer.h"
#include "shader.h"
#include "vertex_array.h"
#include "vertex_buffer.h"
#include "vertex_buffer_layout.h"


#include <imgui/imgui.h>
#include <glm/gtc/matrix_transform.hpp>

#include <array>
#include <memory>

namespace test {


TestTexture2D::TestTexture2D()
    : translationA_{200, 200, 0}, translationB_{400, 200, 0},
        proj_{glm::ortho(0.0f, 640.0f, 0.0f, 480.0f, -1.0f, 1.0f)},
        view_{glm::translate(glm::mat4{1.0f}, glm::vec3{-100, 0, 0})}
{
    std::array<float, 16> positions{
            100.0f, 100.0f, 0.0f, 0.0f, // 0
            200.0f, 100.0f, 1.0f, 0.0f, // 1
            200.0f, 200.0f, 1.0f, 1.0f,  // 2
            100.0f, 200.0f,  0.0f, 1.0f// 3 
        };

        std::array<uint32_t, 6> indices = {
            0, 1, 2, 
            2, 3, 0
        };

        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

        vao_ = std::make_unique<VertexArray>();
        vbo_ = std::make_unique<VertexBuffer>(positions.data(), positions.size() * sizeof(float));
        layout_ = std::make_unique<VertexBufferLayout>();
        layout_->Push<float>(2);
        layout_->Push<float>(2);
        vao_->AddBuffer(*vbo_, *layout_);
        ibo_ = std::make_unique<IndexBuffer>(indices.data(), indices.size());

        shader_ = std::make_unique<Shader>("res/shaders/basic.shader");
        shader_->Bind();
        shader_->SetUniform4f("u_Color", 0.8f, 0.3f, 0.8f, 1.0f);

        texture_ = std::make_unique<Texture>("res/textures/grass.png");
        shader_->SetUniform1i("u_Texture", 0);
}
TestTexture2D::~TestTexture2D()
{

}

void TestTexture2D::OnUpdate(float delta_time)
{

}

void TestTexture2D::OnRender()
{
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    Renderer renderer;
    texture_->Bind();

    {
        glm::mat4 model = glm::translate(glm::mat4{1.0f}, translationA_);
        glm::mat4 mvp = proj_ * view_ * model;
        shader_->Bind();
        shader_->SetUniformMat4f("u_MVP", mvp);
        renderer.Draw(*vao_, *ibo_, *shader_);
    }
    {
        glm::mat4 model = glm::translate(glm::mat4{1.0f}, translationB_);
        glm::mat4 mvp = proj_ * view_ * model;
        shader_->Bind();
        shader_->SetUniformMat4f("u_MVP", mvp);
        renderer.Draw(*vao_, *ibo_, *shader_);
    }
}

void TestTexture2D::OnImGuiRender()
{
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
    
    ImGui::SliderFloat3("translation A", &translationA_.x, 0.0f, 640.0f);            // Edit 1 float using a slider from 0.0f to 1.0f
    ImGui::SliderFloat3("translation B", &translationB_.x, 0.0f, 640.0f);            // Edit 1 float using a slider from 0.0f to 1.0f
    ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / io.Framerate, io.Framerate);
}

} // test
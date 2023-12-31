#include "test_clear_color.h"
#include "renderer.h"

#include <imgui/imgui.h>

namespace test {


ClearColor::ClearColor()
    : clear_color_{ 0.2f, 0.3f, 0.8f, 0.0f }
{

}
ClearColor::~ClearColor()
{

}

void ClearColor::OnUpdate(float delta_time)
{

}

void ClearColor::OnRender()
{
    glClearColor(clear_color_[0], clear_color_[1], clear_color_[2], clear_color_[3]);
    glClear(GL_COLOR_BUFFER_BIT);
}

void ClearColor::OnImGuiRender()
{
    ImGui::ColorEdit4("Clear color", clear_color_);
}

} // test
#include "test_clear_color.h"
#include "renderer.h"

#include <imgui/imgui.h>

namespace test {


CLearColor::CLearColor()
    : clear_color_{ 0.2f, 0.3f, 0.8f, 0.0f }
{

}
CLearColor::~CLearColor()
{

}

void CLearColor::OnUpdate(float delta_time)
{

}

void CLearColor::OnRender()
{
    glClearColor(clear_color_[0], clear_color_[1], clear_color_[2], clear_color_[3]);
    glClear(GL_COLOR_BUFFER_BIT);
}

void CLearColor::OnImGuiRender()
{
    ImGui::ColorEdit4("Clear color", clear_color_);
}

} // test
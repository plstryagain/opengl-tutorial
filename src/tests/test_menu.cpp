#include "test_menu.h"
#include "imgui/imgui.h"

namespace test {


TestMenu::TestMenu(Test*& current_test)
    : current_test_(current_test)
{

}
TestMenu::~TestMenu()
{

}

void TestMenu::OnUpdate(float delta_time)
{

}

void TestMenu::OnRender()
{

}

void TestMenu::OnImGuiRender()
{
    for (auto& test : tests_) {
        if (ImGui::Button(test.first.data())) {
            current_test_ = test.second();
        }
    }
}

} // test
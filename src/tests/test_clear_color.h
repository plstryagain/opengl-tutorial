#pragma once

#include "test.h"

namespace test {

class CLearColor : public Test
{
public:
    CLearColor();
    ~CLearColor();

    void OnUpdate(float delta_time) override;
    void OnRender() override;
    void OnImGuiRender() override;

private:
    float clear_color_[4];
};

} // test
#pragma once

#include "test.h"

namespace test {

class ClearColor : public Test
{
public:
    ClearColor();
    ~ClearColor();

    void OnUpdate(float delta_time) override;
    void OnRender() override;
    void OnImGuiRender() override;

private:
    float clear_color_[4];
};

} // test
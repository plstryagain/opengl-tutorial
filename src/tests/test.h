#pragma once

namespace test {

class Test
{
public:
    Test() {}
    virtual ~Test(){}

    virtual void OnUpdate(float delta_time) = 0;
    virtual void OnRender() = 0;
    virtual void OnImGuiRender() = 0;
};

} // test
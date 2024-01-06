#pragma once

#include "test.h"

#include <vector>
#include <string>
#include <functional>
#include <iostream>

namespace test {

class TestMenu : public Test
{
public:
    TestMenu(Test*& current_test);
    ~TestMenu();
    
    void OnUpdate(float delta_time) override;
    void OnRender() override;
    void OnImGuiRender() override;

    template<typename T>
    void RegisterTest(std::string_view name)
    {
        std::cout << "Registring test: " << name << std::endl;
        tests_.push_back(std::make_pair(name, [](){ return new T{}; }));
    }

private:
    Test*& current_test_;
    std::vector<std::pair<std::string_view, std::function<Test*()>>> tests_;
};


} // test
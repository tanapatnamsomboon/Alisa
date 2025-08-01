#pragma once

#include "Alisa/Core/Base.h"
#include "Alisa/Core/Application.h"

extern Alisa::Application* Alisa::CreateApplication();

int main(int argc, char** argv)
{
    Alisa::Log::Init();

    auto app = Alisa::CreateApplication();

    app->Run();

    delete app;

    return 0;
}

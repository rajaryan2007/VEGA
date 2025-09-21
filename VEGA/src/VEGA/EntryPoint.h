#pragma once

#ifdef VG_PLATFORM_WINDOWS

extern VEGA::Application* VEGA::CreateApplication();

int main(int argc, char** argv)
{
  
    auto app = VEGA::CreateApplication();
    app->Run();
    delete app;
    return 0;
}

#endif



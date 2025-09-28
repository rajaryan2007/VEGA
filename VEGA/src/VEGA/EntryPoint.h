#pragma once

#ifdef VG_PLATFORM_WINDOWS

extern VEGA::Application* VEGA::CreateApplication();

int main(int argc, char** argv)
{
	VEGA::Log::Init();
	VG_CORE_ERROR("VEGA Engine Initialized!");
	VG_INFO("Welcome to VEGA Engine!");
    auto app = VEGA::CreateApplication();
    app->Run();
    delete app;
    return 0;
}

#endif

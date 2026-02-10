#pragma once

#ifdef VG_PLATFORM_WINDOWS

extern VEGA::Application* VEGA::CreateApplication();

int main(int argc, char** argv)
{
	VEGA::Log::Init();
    VG_PROFILE_BEGIN_SESSION("startup", "VegaProfile.Startup.josn");
    auto app = VEGA::CreateApplication();
    VG_PROFILE_END_SESSION();
    VG_PROFILE_BEGIN_SESSION("Runtime", "VegaProfile.runtime.josn");
    app->Run();
    VG_PROFILE_END_SESSION();
    VG_PROFILE_BEGIN_SESSION("shutdown", "VegaProfile.Shutdown.josn");
    delete app;
    VG_PROFILE_END_SESSION();
    return 0;
}
#endif

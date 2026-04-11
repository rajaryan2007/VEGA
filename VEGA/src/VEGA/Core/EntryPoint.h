#pragma once
#include "VEGA/AssestsManager/VfsSystem.h"

#ifdef VG_PLATFORM_WINDOWS

extern VEGA::Application* VEGA::CreateApplication();

int main(int argc, char** argv)
{
    VEGA::FileSystem::Get().Initialize(argv[0]);
	VEGA::Log::Init();
    auto app = VEGA::CreateApplication();
    
    app->Run();

    delete app;
    return 0;
}
#endif

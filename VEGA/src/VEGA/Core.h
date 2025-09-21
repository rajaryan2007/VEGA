#pragma once
#ifdef VG_PLATFORM_WINDOWS
      #ifdef VG_BUILD_DLL
             #define  VEGA_API __declspec(dllexport)
      #else
             #define VEGA_API __declspec(dllimport)
      #endif // HZ_BUILD_DLL
#else
       #error Vega only support Window!
#endif

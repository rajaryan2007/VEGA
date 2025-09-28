#pragma once
#include "Core.h"
#include "spdlog/spdlog.h"
#include <memory>
namespace VEGA {

   class VEGA_API Log
   {
    public:
		static void Init();
		inline static std::shared_ptr<spdlog::logger>& GetCoreLogger() { return s_CoreLogger; }
		inline static std::shared_ptr<spdlog::logger>& GetClientLogger() { return s_ClientLogger; }

   private:
	   static std::shared_ptr<spdlog::logger> s_CoreLogger;
	   static std::shared_ptr <spdlog::logger> s_ClientLogger;

	  
    };

}


//core log macros
#define VG_CORE_ERROR(...) ::VEGA::Log::GetCoreLogger()->error(__VA_ARGS__);
#define VG_CORE_WARN(...)  ::VEGA::Log::GetCoreLogger()->warn(__VA_ARGS__);
#define VG_CORE_INFO(...)  ::VEGA::Log::GetCoreLogger()->info(__VA_ARGS__);
#define VG_CORE_TRACE(...) ::VEGA::Log::GetCoreLogger()->trace(__VA_ARGS__);
#define VG_CORE_FATAL(...) ::VEGA::Log::GetCoreLogger()->fatal(__VA_ARGS__);

//client log macros
#define VG_TRACE(...)  ::VEGA::Log::GetClientLogger()->trace(__VA_ARGS__);
#define VG_WARN(...)   ::VEGA::Log::GetClientLogger()->warn(__VA_ARGS__);
#define VG_INFO(...)   ::VEGA::Log::GetClientLogger()->info(__VA_ARGS__);
#define VG_FATAL(...)  ::VEGA::Log::GetClientLogger()->fatal(__VA_ARGS__);
#define VG_ERROR(...)  ::VEGA::Log::GetClientLogger()->error(__VA_ARGS__);

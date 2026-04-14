#pragma once

#include "spdlog/spdlog.h"
#include "Core.h"
#include "UHE/ImGui/ImGuiLogsink.h"

namespace UHE {

	class UHE_API Log
	{
	public:
		static void Init();
		inline static std::shared_ptr<spdlog::logger>& GetCoreLogger() { return s_CoreLogger; }
		inline static std::shared_ptr<spdlog::logger>& GetClientLogger() { return s_ClientLogger; }

	public:
		static std::shared_ptr<ImGuiLogSink<std::mutex>> GetImGuiSink() { return s_ImGuiSink; }

	private:
		static std::shared_ptr<ImGuiLogSink<std::mutex>> s_ImGuiSink;

	private:
		static std::shared_ptr<spdlog::logger> s_CoreLogger;
		static std::shared_ptr <spdlog::logger> s_ClientLogger;


	};

}



#define VG_CORE_ERROR(...)    ::UHE::Log::GetCoreLogger()->error(__VA_ARGS__)
#define VG_CORE_WARN(...)     ::UHE::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define VG_CORE_INFO(...)     ::UHE::Log::GetCoreLogger()->info(__VA_ARGS__)
#define VG_CORE_TRACE(...)    ::UHE::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define VG_CORE_CRITICAL(...) ::UHE::Log::GetCoreLogger()->critical(__VA_ARGS__)


#define VG_TRACE(...)    ::UHE::Log::GetClientLogger()->trace(__VA_ARGS__)
#define VG_WARN(...)     ::UHE::Log::GetClientLogger()->warn(__VA_ARGS__)
#define VG_INFO(...)     ::UHE::Log::GetClientLogger()->info(__VA_ARGS__)
#define VG_CRITICAL(...) ::UHE::Log::GetClientLogger()->critical(__VA_ARGS__)
#define VG_ERROR(...)    ::UHE::Log::GetClientLogger()->error(__VA_ARGS__)

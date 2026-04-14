#include <uhepch.h>
#include "Log.h"



#include <spdlog/sinks/stdout_color_sinks.h>



namespace UHE {
	std::shared_ptr<spdlog::logger> Log::s_CoreLogger;
	std::shared_ptr <spdlog::logger> Log::s_ClientLogger;
	
	std::shared_ptr<ImGuiLogSink<std::mutex>> Log::s_ImGuiSink;

	void Log::Init()
	{
		spdlog::set_pattern("%^[%T] %n: %v%$");

		auto consoleSink = std::make_shared<spdlog::sinks::stdout_color_sink_mt>();
		s_ImGuiSink = std::make_shared<ImGuiLogSink<std::mutex>>();

		std::vector<spdlog::sink_ptr> sinks{ consoleSink, s_ImGuiSink };

		s_CoreLogger = std::make_shared<spdlog::logger>("UHE", sinks.begin(), sinks.end());
		s_CoreLogger->set_level(spdlog::level::trace);

		s_ClientLogger = std::make_shared<spdlog::logger>("APP", sinks.begin(), sinks.end());
		s_ClientLogger->set_level(spdlog::level::trace);
	}
	
}
#pragma once
#include "vgpch.h"
#include "spdlog/sinks/base_sink.h"
#include <mutex>

namespace VEGA {

	struct ImGuiLogEntry   
	{
		std::string Message;
		spdlog::level::level_enum Level;
	};

	template<typename Mutex>
	class ImGuiLogSink   
		: public spdlog::sinks::base_sink<Mutex>
	{
	public:
		const std::vector<ImGuiLogEntry>& GetLogs() const { return m_Logs; }

		void Clear() { m_Logs.clear(); }

	protected:
		void sink_it_(const spdlog::details::log_msg& msg) override {
			spdlog::memory_buf_t formatted;
			this->formatter_->format(msg, formatted);

			ImGuiLogEntry entry;
			entry.Message = fmt::to_string(formatted);
			entry.Level = msg.level;

			m_Logs.push_back(entry);

			if (m_Logs.size() > 2000)
				m_Logs.erase(m_Logs.begin());
		}

		void flush_() override {}

	private:
		std::vector<ImGuiLogEntry> m_Logs;
	};
}
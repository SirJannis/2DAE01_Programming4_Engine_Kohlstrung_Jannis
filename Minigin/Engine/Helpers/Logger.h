#pragma once
#include "../Helpers/Singleton.h"
namespace MyEngine
{
	enum class LogLevel
	{
		Info,
		Warning,
		Error
	};

	class Logger final : public Singleton<Logger>
	{
	public:
		void Init();
		void Log(LogLevel level, const std::string& msg) const;
		void LogInfo(const std::string& msg) const;
		void LogWarning(const std::string& msg) const;
		void LogError(const std::string& msg) const;

	private:
		HANDLE m_ConsoleHandle;
	};
}

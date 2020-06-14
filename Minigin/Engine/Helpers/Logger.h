#pragma once
#include <iostream>
namespace MyEngine
{
	enum class LogLevel
	{
		Info,
		Warning,
		Error
	};

	class Logger final
	{
	public:
		static void Init();
		static void Log(LogLevel level, const std::string& msg);
		static void LogInfo(const std::string& msg);
		static void LogWarning(const std::string& msg);
		static void LogError(const std::string& msg);

	private:
		static bool m_IsInitialized;
		static HANDLE m_ConsoleHandle;
	};
}

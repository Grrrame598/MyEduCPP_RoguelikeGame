#include "pch.h"
#include "Logger.h"

#include <filesystem>
#include <iostream>
#include <sstream>

namespace fs = std::filesystem;

namespace XYZEngine
{
	std::string LogLevelToString(LogLevel level)
	{
		switch (level)
		{
		case LogLevel::INFO: return "[INFO]";
		case LogLevel::WARNING: return "[WARNING]";
		case LogLevel::ERROR: return "[ERROR]";
		default: return "[UNKNOWN]";
		}
	}

	void ConsoleSink::Log(LogLevel level, const std::string& message)
	{
		std::cout << LogLevelToString(level) << " " << message << std::endl;
	}

	FileSink::FileSink(const std::string& filename)
	{
		fs::path filePath(filename);
		fs::path directory = filePath.parent_path();

		if (!directory.empty() && !fs::exists(directory))
		{
			fs::create_directories(directory);
		}

		logFile.open(filePath, std::ios::app);
	}

	FileSink::~FileSink()
	{
		if (logFile.is_open())
		{
			logFile.close();
		}
	}

	void FileSink::Log(LogLevel level, const std::string& message)
	{
		if (logFile)
		{
			logFile << LogLevelToString(level) << " " << message << std::endl;
		}
	}

	bool FileSink::IsOpen() const
	{
		return logFile.is_open();
	}

	void Logger::AddSink(const std::shared_ptr<LogSink>& sink)
	{
		std::lock_guard<std::mutex> lock(logMutex);
		sinks.push_back(sink);
	}

	void Logger::SetMinLevel(LogLevel level)
	{
		std::lock_guard<std::mutex> lock(logMutex);
		minLevel = level;
	}

	LogLevel Logger::GetMinLevel() const
	{
		return minLevel;
	}

	void Logger::Log(LogLevel level, const std::string& message)
	{
		// Отбрасываем менее важные сообщения
		if (static_cast<int>(level) < static_cast<int>(minLevel))
		{
			return;
		}

		std::lock_guard<std::mutex> lock(logMutex);
		for (auto& sink : sinks)
		{
			if (sink)
			{
				sink->Log(level, message);
			}
		}
	}

	void Logger::Info(const std::string& message)
	{
		Log(LogLevel::INFO, message);
	}

	void Logger::Warn(const std::string& message)
	{
		Log(LogLevel::WARNING, message);
	}

	void Logger::Error(const std::string& message)
	{
		Log(LogLevel::ERROR, message);
	}

	LoggerRegistry& LoggerRegistry::Instance()
	{
		static LoggerRegistry instance;
		return instance;
	}

	std::shared_ptr<Logger> LoggerRegistry::GetLogger(const std::string& name)
	{
		std::lock_guard<std::mutex> lock(registryMutex);
		auto it = loggers.find(name);
		if (it != loggers.end())
		{
			return it->second;
		}
		return defaultLogger;
	}

	void LoggerRegistry::RegisterLogger(const std::string& name, std::shared_ptr<Logger> logger)
	{
		std::lock_guard<std::mutex> lock(registryMutex);
		loggers[name] = logger;
	}

	void LoggerRegistry::SetDefaultLogger(std::shared_ptr<Logger> logger)
	{
		std::lock_guard<std::mutex> lock(registryMutex);
		defaultLogger = logger;
	}

	std::shared_ptr<Logger> LoggerRegistry::GetDefaultLogger()
	{
		std::lock_guard<std::mutex> lock(registryMutex);
		return defaultLogger;
	}

	std::string FormatLogMessage(const std::string& message, const char* file, int line, const char* function)
	{
		std::ostringstream ss;
		ss << message;
		if (file != nullptr && function != nullptr)
		{
			ss << " (" << file << ":" << line << ", " << function << ")";
		}
		return ss.str();
	}
} // namespace XYZEngine



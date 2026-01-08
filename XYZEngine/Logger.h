#pragma once

#include <string>
#include <vector>
#include <memory>
#include <mutex>
#include <unordered_map>
#include <fstream>

// Все комментарии на русском согласно требованиям

namespace XYZEngine
{
	// Уровни логирования (минимальный набор из урока)
	enum class LogLevel
	{
		INFO = 0,
		WARNING = 1,
		ERROR = 2
	};

	// Преобразование уровня в читаемый тег
	std::string LogLevelToString(LogLevel level);

	// Стратегия вывода логов
	class LogSink
	{
	public:
		virtual ~LogSink() = default;
		virtual void Log(LogLevel level, const std::string& message) = 0;
	};

	// Вывод в консоль
	class ConsoleSink : public LogSink
	{
	public:
		void Log(LogLevel level, const std::string& message) override;
	};

	// Вывод в файл
	class FileSink : public LogSink
	{
	public:
		explicit FileSink(const std::string& filename);
		~FileSink();

		void Log(LogLevel level, const std::string& message) override;
		bool IsOpen() const;

	private:
		std::ofstream logFile;
	};

	// Центральный логгер, отправляет сообщения во все зарегистрированные sink-и
	class Logger
	{
	public:
		void AddSink(const std::shared_ptr<LogSink>& sink);

		void SetMinLevel(LogLevel level);
		LogLevel GetMinLevel() const;

		void Log(LogLevel level, const std::string& message);
		void Info(const std::string& message);
		void Warn(const std::string& message);
		void Error(const std::string& message);

	private:
		std::vector<std::shared_ptr<LogSink>> sinks;
		std::mutex logMutex;
		LogLevel minLevel = LogLevel::INFO;
	};

	// Реестр логгеров (Singleton)
	class LoggerRegistry
	{
	public:
		static LoggerRegistry& Instance();

		std::shared_ptr<Logger> GetLogger(const std::string& name);
		void RegisterLogger(const std::string& name, std::shared_ptr<Logger> logger);

		void SetDefaultLogger(std::shared_ptr<Logger> logger);
		std::shared_ptr<Logger> GetDefaultLogger();

	private:
		LoggerRegistry() = default;
		LoggerRegistry(const LoggerRegistry&) = delete;
		LoggerRegistry& operator=(const LoggerRegistry&) = delete;

		std::unordered_map<std::string, std::shared_ptr<Logger>> loggers;
		std::shared_ptr<Logger> defaultLogger = nullptr;
		std::mutex registryMutex;
	};

	// Формирование сообщения с контекстом (файл, строка, функция)
	std::string FormatLogMessage(const std::string& message, const char* file, int line, const char* function);
} // namespace XYZEngine

// Макросы для удобного вызова
#define LOG_INFO(message) \
	do { auto logger = XYZEngine::LoggerRegistry::Instance().GetDefaultLogger(); if (logger) { logger->Log(XYZEngine::LogLevel::INFO, XYZEngine::FormatLogMessage((message), __FILE__, __LINE__, __FUNCTION__)); } } while (0)

#define LOG_WARN(message) \
	do { auto logger = XYZEngine::LoggerRegistry::Instance().GetDefaultLogger(); if (logger) { logger->Log(XYZEngine::LogLevel::WARNING, XYZEngine::FormatLogMessage((message), __FILE__, __LINE__, __FUNCTION__)); } } while (0)

#define LOG_ERROR(message) \
	do { auto logger = XYZEngine::LoggerRegistry::Instance().GetDefaultLogger(); if (logger) { logger->Log(XYZEngine::LogLevel::ERROR, XYZEngine::FormatLogMessage((message), __FILE__, __LINE__, __FUNCTION__)); } } while (0)



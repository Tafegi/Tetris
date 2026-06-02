#include "Logger.h"

#include <chrono>
#include <iomanip>
#include <sstream>

namespace core
{
    Logger::Logger(const std::string& filePath)
        : file_(filePath, std::ios::app)
    {
    }

    void Logger::log(LogLevel level, std::string_view message)
    {
        std::lock_guard lock(mutex_);

        auto now = std::chrono::system_clock::now();
        auto time = std::chrono::system_clock::to_time_t(now);

        std::tm tm{};
#ifdef _WIN32
        localtime_s(&tm, &time);
#else
        localtime_r(&time, &tm);
#endif

        file_ << std::put_time(&tm, "%Y-%m-%d %H:%M:%S")
              << " [" << toString(level) << "] "
              << message << '\n';
    }

    void Logger::debug(std::string_view message) { log(LogLevel::Debug, message); }
    void Logger::info(std::string_view message) { log(LogLevel::Info, message); }
    void Logger::warning(std::string_view message) { log(LogLevel::Warning, message); }
    void Logger::error(std::string_view message) { log(LogLevel::Error, message); }
    void Logger::critical(std::string_view message) { log(LogLevel::Critical, message); }

    std::string_view Logger::toString(LogLevel level)
    {
        switch (level)
        {
            case LogLevel::Debug: return "DEBUG";
            case LogLevel::Info: return "INFO";
            case LogLevel::Warning: return "WARN";
            case LogLevel::Error: return "ERROR";
            case LogLevel::Critical: return "CRITICAL";
        }
        return "UNKNOWN";
    }
}
#pragma once

#include <string>
#include <fstream>
#include <mutex>
#include <string_view>

namespace core
{
    enum class LogLevel
    {
        Debug,
        Info,
        Warning,
        Error,
        Critical
    };

    class Logger
    {
    public:
        explicit Logger(const std::string& filePath);

        void log(LogLevel level, std::string_view message);

        void debug(std::string_view message);
        void info(std::string_view message);
        void warning(std::string_view message);
        void error(std::string_view message);
        void critical(std::string_view message);

    private:
        std::ofstream file_;
        std::mutex mutex_;

        static std::string_view toString(LogLevel level);
    };
}
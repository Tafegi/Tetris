#pragma once

#include <stdexcept>
#include <string>

namespace core
{
    class GameException : public std::runtime_error
    {
    public:
        explicit GameException(const std::string& message)
            : std::runtime_error(message) {}
    };

    class ResourceException : public GameException
    {
    public:
        explicit ResourceException(const std::string& message)
            : GameException(message) {}
    };

    class ConfigException : public GameException
    {
    public:
        explicit ConfigException(const std::string& message)
            : GameException(message) {}
    };
}
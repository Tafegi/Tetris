#pragma once

#include <string>
#include <optional>

namespace interfaces
{
    template<typename T>
    class IRepository
    {
    public:
        virtual ~IRepository() = default;

        virtual void save(const std::string& key, const T& value) = 0;
        virtual std::optional<T> load(const std::string& key) = 0;
        virtual void remove(const std::string& key) = 0;
    };
}
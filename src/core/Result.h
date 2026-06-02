#pragma once

#include <variant>
#include <string>

namespace core
{
    template<typename T>
    class Result
    {
    public:
        static Result success(T value)
        {
            return Result(std::move(value));
        }

        static Result failure(std::string error)
        {
            return Result(std::move(error));
        }

        bool isSuccess() const { return std::holds_alternative<T>(data_); }
        bool isFailure() const { return !isSuccess(); }

        T& value() { return std::get<T>(data_); }
        const T& value() const { return std::get<T>(data_); }

        const std::string& error() const { return std::get<std::string>(data_); }

    private:
        std::variant<T, std::string> data_;

        explicit Result(T value)
            : data_(std::move(value)) {}

        explicit Result(std::string error)
            : data_(std::move(error)) {}
    };
}
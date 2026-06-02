#include "JsonRepository.h"
#include <fstream>
#include <filesystem>

namespace service
{
    void JsonRepository::save(const std::string& key, const std::string& value)
    {
        std::ofstream file(key);
        if (file.is_open())
        {
            file << value;
        }
    }

    std::optional<std::string> JsonRepository::load(const std::string& key)
    {
        std::ifstream file(key);
        if (!file.is_open())
        {
            return std::nullopt;
        }

        std::string content((std::istreambuf_iterator<char>(file)),
                             std::istreambuf_iterator<char>());
        return content;
    }

    void JsonRepository::remove(const std::string& key)
    {
        std::filesystem::remove(key);
    }
}
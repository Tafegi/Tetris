#pragma once

#include <string>
#include <optional>
#include "interfaces/IRepository.h"

namespace service
{
    // Наслідуємо шаблонний інтерфейс interfaces::IRepository із типом std::string
    class JsonRepository final : public interfaces::IRepository<std::string>
    {
    public:
        JsonRepository() = default;

        // Сигнатури тепер суворо відповідають інтерфейсу (void замість bool, key замість path)
        void save(const std::string& key, const std::string& value) override;
        std::optional<std::string> load(const std::string& key) override;
        void remove(const std::string& key) override;
    };
}
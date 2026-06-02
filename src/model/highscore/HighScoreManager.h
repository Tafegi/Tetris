#pragma once

#include <vector>
#include <string>
#include <cstdint>

namespace model
{
    struct HighScoreEntry
    {
        std::string playerName;
        std::int64_t score{};
        std::int32_t level{};
        std::int32_t lines{};
        std::int64_t durationSec{};
        std::string date;
    };

    class HighScoreManager
    {
    public:
        HighScoreManager();

        void load(const std::string& path);
        void save(const std::string& path) const;

        void add(const HighScoreEntry& entry);

        const std::vector<HighScoreEntry>& entries() const noexcept;

        void clear();

    private:
        void sort();
        void trim();

    private:
        std::vector<HighScoreEntry> entries_;
        static constexpr std::size_t MAX_SIZE = 20;
    };
}
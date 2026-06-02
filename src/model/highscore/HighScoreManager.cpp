#include "HighScoreManager.h"

#include <fstream>
#include <algorithm>

namespace model
{
    HighScoreManager::HighScoreManager() = default;

    const std::vector<HighScoreEntry>& HighScoreManager::entries() const noexcept
    {
        return entries_;
    }

    void HighScoreManager::add(const HighScoreEntry& entry)
    {
        entries_.push_back(entry);

        sort();
        trim();
    }

    void HighScoreManager::sort()
    {
        std::sort(entries_.begin(), entries_.end(),
            [](const HighScoreEntry& a, const HighScoreEntry& b)
            {
                return a.score > b.score;
            });
    }

    void HighScoreManager::trim()
    {
        if (entries_.size() > MAX_SIZE)
        {
            entries_.resize(MAX_SIZE);
        }
    }

    void HighScoreManager::clear()
    {
        entries_.clear();
    }

    void HighScoreManager::load(const std::string& path)
    {
        std::ifstream file(path);
        if (!file.is_open())
            return;

        entries_.clear();

        HighScoreEntry e;

        while (file >>
               e.playerName >>
               e.score >>
               e.level >>
               e.lines >>
               e.durationSec >>
               e.date)
        {
            entries_.push_back(e);
        }

        sort();
        trim();
    }

    void HighScoreManager::save(const std::string& path) const
    {
        std::ofstream file(path);

        for (const auto& e : entries_)
        {
            file << e.playerName << " "
                 << e.score << " "
                 << e.level << " "
                 << e.lines << " "
                 << e.durationSec << " "
                 << e.date << "\n";
        }
    }
}
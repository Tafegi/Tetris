#pragma once

/**
 * @brief Tracks total lines cleared and derives the current level.
 *
 * Uses Guideline progression: level = (totalLines / 10) + 1, capped at 15.
 * Drop interval follows the Guideline formula (frames at 60 fps then converted).
 */
class LevelSystem
{
public:
    LevelSystem() = default;

    void     addLines(int lines) noexcept;
    void     reset() noexcept;

    [[nodiscard]] int      getLevel()      const noexcept { return m_level; }
    [[nodiscard]] int      getTotalLines() const noexcept { return m_totalLines; }

    /// Gravity interval in seconds (how long before the piece drops one row)
    [[nodiscard]] float    getDropInterval() const noexcept;

private:
    void updateLevel() noexcept;

    int m_totalLines{0};
    int m_level{1};

    static constexpr int k_maxLevel = 15;
};
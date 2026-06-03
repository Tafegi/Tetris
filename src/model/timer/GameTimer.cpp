#include "GameTimer.h"

GameTimer::GameTimer(float interval) noexcept
    : m_interval(interval)
{}

void GameTimer::setInterval(float seconds) noexcept
{
    m_interval = seconds;
}

void GameTimer::reset() noexcept
{
    m_accumulated = 0.0f;
}

bool GameTimer::update(float deltaTime) noexcept
{
    m_accumulated += deltaTime;
    if (m_accumulated >= m_interval)
    {
        m_accumulated -= m_interval;
        return true;
    }
    return false;
}
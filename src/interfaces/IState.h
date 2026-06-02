#pragma once

#include <SFML/Window/Event.hpp>

namespace state
{
    class IState
    {
    public:
        virtual ~IState() = default;

        // Саме ці три методи перевизначають усі твої стани в папці src/state/
        virtual void handleEvent(const sf::Event& event) = 0;
        virtual void update(float dt) = 0;
        virtual void render() = 0;
    };
}
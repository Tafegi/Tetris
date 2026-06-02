
#pragma once

#include <vector>
#include <memory>

#include <SFML/System/Clock.hpp>
#include <SFML/Graphics/RectangleShape.hpp>

namespace view
{
    struct Animation
    {
        sf::RectangleShape shape;

        sf::Vector2f startPos;
        sf::Vector2f endPos;

        float duration{};
        float elapsed{};

        bool finished{false};
    };

    class AnimationSystem
    {
    public:
        AnimationSystem();

        void update(float dt);
        void draw(sf::RenderTarget& target);

        void addAnimation(const Animation& animation);

        void clear();

    private:
        float lerp(float a, float b, float t) const;

        sf::Vector2f lerp(const sf::Vector2f& a,
                          const sf::Vector2f& b,
                          float t) const;

    private:
        std::vector<Animation> animations_;
    };
}
#include "AnimationSystem.h"
#include <SFML/Graphics/RenderTarget.hpp>
namespace view
{
    AnimationSystem::AnimationSystem() = default;

    void AnimationSystem::update(float dt)
    {
        for (auto& anim : animations_)
        {
            if (anim.finished)
                continue;

            anim.elapsed += dt;

            float t = anim.elapsed / anim.duration;
            if (t >= 1.0f)
            {
                t = 1.0f;
                anim.finished = true;
            }

            sf::Vector2f newPos = lerp(anim.startPos, anim.endPos, t);
            anim.shape.setPosition(newPos);
        }

        // remove finished animations
        animations_.erase(
            std::remove_if(
                animations_.begin(),
                animations_.end(),
                [](const Animation& a)
                {
                    return a.finished;
                }),
            animations_.end()
        );
    }

    void AnimationSystem::draw(sf::RenderTarget& target)
    {
        for (const auto& anim : animations_)
        {
            target.draw(anim.shape);
        }
    }

    void AnimationSystem::addAnimation(const Animation& animation)
    {
        animations_.push_back(animation);
    }

    void AnimationSystem::clear()
    {
        animations_.clear();
    }

    float AnimationSystem::lerp(float a, float b, float t) const
    {
        return a + (b - a) * t;
    }

    sf::Vector2f AnimationSystem::lerp(const sf::Vector2f& a,
                                       const sf::Vector2f& b,
                                       float t) const
    {
        return {
            lerp(a.x, b.x, t),
            lerp(a.y, b.y, t)
        };
    }
}
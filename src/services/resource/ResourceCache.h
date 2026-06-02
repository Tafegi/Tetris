#pragma once

#include <memory>
#include <string>
#include <unordered_map>

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

namespace service
{
    class ResourceCache
    {
    public:
        ResourceCache() = default;

        const sf::Texture& getTexture(const std::string& path);
        const sf::Font& getFont(const std::string& path);
        const sf::SoundBuffer& getSound(const std::string& path);
        const sf::Music& getMusic(const std::string& path);

        void clear();

    private:
        std::unordered_map<std::string, std::unique_ptr<sf::Texture>> textures_;
        std::unordered_map<std::string, std::unique_ptr<sf::Font>> fonts_;
        std::unordered_map<std::string, std::unique_ptr<sf::SoundBuffer>> sounds_;
        std::unordered_map<std::string, std::unique_ptr<sf::Music>> music_;
    };
}
#include "ResourceCache.h"
#include <stdexcept>

namespace service
{
    const sf::Texture& ResourceCache::getTexture(const std::string& path)
    {
        auto it = textures_.find(path);
        if (it != textures_.end())
            return *it->second;

        auto texture = std::make_unique<sf::Texture>();

        if (!texture->loadFromFile(path))
            throw std::runtime_error("Failed to load texture: " + path);

        const auto& ref = *texture;
        textures_[path] = std::move(texture);

        return ref;
    }

    const sf::Font& ResourceCache::getFont(const std::string& path)
    {
        auto it = fonts_.find(path);
        if (it != fonts_.end())
            return *it->second;

        auto font = std::make_unique<sf::Font>();

        if (!font->openFromFile(path))
            throw std::runtime_error("Failed to load font: " + path);

        const auto& ref = *font;
        fonts_[path] = std::move(font);

        return ref;
    }

    const sf::SoundBuffer& ResourceCache::getSound(const std::string& path)
    {
        auto it = sounds_.find(path);
        if (it != sounds_.end())
            return *it->second;

        auto buffer = std::make_unique<sf::SoundBuffer>();

        if (!buffer->loadFromFile(path))
            throw std::runtime_error("Failed to load sound: " + path);

        const auto& ref = *buffer;
        sounds_[path] = std::move(buffer);

        return ref;
    }

    const sf::Music& ResourceCache::getMusic(const std::string& path)
    {
        auto it = music_.find(path);
        if (it != music_.end())
            return *it->second;

        auto music = std::make_unique<sf::Music>();

        if (!music->openFromFile(path))
            throw std::runtime_error("Failed to load music: " + path);

        const auto& ref = *music;
        music_[path] = std::move(music);

        return ref;
    }

    void ResourceCache::clear()
    {
        textures_.clear();
        fonts_.clear();
        sounds_.clear();
        music_.clear();
    }
}
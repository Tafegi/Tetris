#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include <string>

namespace view
{
    enum class SettingsOption
    {
        Resolution,
        Fullscreen,
        MasterVolume,
        MusicVolume,
        SfxVolume,
        DAS,
        ARR,
        GhostPiece,
        FpsLimit,
        VSync,
        Back
    };

    class SettingsView
    {
    public:
        explicit SettingsView(sf::RenderWindow& window);

        void update(float dt);
        void render();

        void moveUp();
        void moveDown();

        int selectedIndex() const noexcept;

        void increaseValue();
        void decreaseValue();

    private:
        void drawBackground();
        void drawTitle();
        void drawItems();

        void animate(float dt);

    private:
        sf::RenderWindow& window_;
        sf::Font font_;

        sf::Text title_;

        std::vector<sf::Text> items_;
        std::vector<std::string> labels_;

        int selectedIndex_{0};
        float anim_{0.f};
    };
}
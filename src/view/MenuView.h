#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include <string>

namespace view
{
    enum class MenuOption
    {
        StartGame,
        Statistics,
        Leaderboard,
        Settings,
        Exit
    };

    class MenuView
    {
    public:
        explicit MenuView(sf::RenderWindow& window);

        void update(float dt);
        void render();

        void moveUp();
        void moveDown();

        MenuOption selectedOption() const;

    private:
        void drawBackground();
        void drawTitle();
        void drawItems();
        void animateSelection(float dt);

    private:
        sf::RenderWindow& window_;
        sf::Font font_;

        sf::Text titleText_;
        std::vector<std::string> labels_;
        std::vector<sf::Text> items_; // Твої елементи меню

        int selectedIndex_{0};
        float selectorAnim_{0.f};
    };
}
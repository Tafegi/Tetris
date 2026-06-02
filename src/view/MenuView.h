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

        // BUG FIX: added mouse support
        // Returns true if a click landed on a menu item (updates selection)
        bool handleMouseMove(sf::Vector2i mousePos);
        bool handleMouseClick(sf::Vector2i mousePos);

        MenuOption selectedOption() const;

    private:
        void drawBackground();
        void drawTitle();
        void drawItems();
        void animateSelection(float dt);

        // Returns screen rect of menu item i
        sf::FloatRect itemRect(int i) const;

    private:
        sf::RenderWindow& window_;
        sf::Font font_;

        sf::Text titleText_;
        std::vector<std::string> labels_;
        std::vector<sf::Text> items_;

        int selectedIndex_{0};
        float selectorAnim_{0.f};

        static constexpr float ITEM_START_Y = 220.f;
        static constexpr float ITEM_STEP    = 60.f;
        static constexpr float ITEM_X       = 120.f;
    };
}
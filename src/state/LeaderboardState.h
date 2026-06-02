#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include <string>

#include "../interfaces/IState.h"
#include "../controller/StateMachine.h"
#include "../model/highscore/HighScoreManager.h"

namespace state
{
    class LeaderboardState final : public IState
    {
    public:
        LeaderboardState(sf::RenderWindow& window,
                         controller::StateMachine& stateMachine,
                         const model::HighScoreManager& highScores);

        void handleEvent(const sf::Event& event) override;
        void update(float dt) override;
        void render() override;

    private:
        void drawUI();

    private:
        sf::RenderWindow& window_;
        controller::StateMachine& stateMachine_;
        const model::HighScoreManager& highScores_;

        sf::Font font_;
        sf::Text titleText_;
        sf::Text listText_;
    };
}
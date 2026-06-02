#pragma once

#include "../interfaces/IState.h"
#include "../controller/StateMachine.h"
#include "../model/statistics/StatisticsManager.h"
#include "../view/StatisticsView.h"
#include <SFML/Graphics.hpp>

namespace state
{
    class StatisticsState final : public IState
    {
    public:
        StatisticsState(sf::RenderWindow& window,
                        controller::StateMachine& stateMachine,
                        const model::StatisticsManager& stats);

        void handleEvent(const sf::Event& event) override;
        void update(float dt) override;
        void render() override;

    private:
        sf::RenderWindow& window_;
        controller::StateMachine& stateMachine_;
        const model::StatisticsManager& stats_;

        view::StatisticsView statisticsView_;
    };
}
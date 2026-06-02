#pragma once

#include "../interfaces/IState.h"
#include "../controller/StateMachine.h"
#include "../model/settings/SettingsManager.h"
#include "../view/SettingsView.h"
#include <SFML/Graphics.hpp>

namespace state
{
    class SettingsState final : public IState
    {
    public:
        SettingsState(sf::RenderWindow& window,
                      controller::StateMachine& stateMachine,
                      model::SettingsManager& settings);

        void handleEvent(const sf::Event& event) override;
        void update(float dt) override;
        void render() override;

    private:
        sf::RenderWindow& window_;
        controller::StateMachine& stateMachine_;
        model::SettingsManager& settings_;

        view::SettingsView settingsView_;
    };
}
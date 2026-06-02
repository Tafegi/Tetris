#include "SettingsManager.h"

#include <fstream>

namespace model
{
    SettingsManager::SettingsManager()
    {
        resetToDefault();
    }

    void SettingsManager::resetToDefault()
    {
        settings_.resolutionWidth = 1280;
        settings_.resolutionHeight = 720;
        settings_.fullscreen = false;

        settings_.masterVolume = 1.0f;
        settings_.musicVolume = 0.7f;
        settings_.sfxVolume = 1.0f;

        settings_.das = 150;
        settings_.arr = 50;

        settings_.ghostPiece = true;
        settings_.fpsLimit = 60;
        settings_.vSync = true;
    }

    Settings& SettingsManager::settings()
    {
        return settings_;
    }

    const Settings& SettingsManager::settings() const
    {
        return settings_;
    }

    void SettingsManager::load(const std::string& path)
    {
        std::ifstream file(path);
        if (!file.is_open())
        {
            resetToDefault();
            return;
        }

        file >>
            settings_.resolutionWidth >>
            settings_.resolutionHeight >>
            settings_.fullscreen >>
            settings_.masterVolume >>
            settings_.musicVolume >>
            settings_.sfxVolume >>
            settings_.das >>
            settings_.arr >>
            settings_.ghostPiece >>
            settings_.fpsLimit >>
            settings_.vSync;
    }

    void SettingsManager::save(const std::string& path) const
    {
        std::ofstream file(path);

        file <<
            settings_.resolutionWidth << " " <<
            settings_.resolutionHeight << " " <<
            settings_.fullscreen << " " <<
            settings_.masterVolume << " " <<
            settings_.musicVolume << " " <<
            settings_.sfxVolume << " " <<
            settings_.das << " " <<
            settings_.arr << " " <<
            settings_.ghostPiece << " " <<
            settings_.fpsLimit << " " <<
            settings_.vSync;
    }
}
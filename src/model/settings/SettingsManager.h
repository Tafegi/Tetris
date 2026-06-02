#pragma once

#include <string>

namespace model
{
    struct Settings
    {
        int resolutionWidth{};
        int resolutionHeight{};
        bool fullscreen{};

        float masterVolume{};
        float musicVolume{};
        float sfxVolume{};

        int das{};   // Delayed Auto Shift
        int arr{};   // Auto Repeat Rate

        bool ghostPiece{};
        int fpsLimit{};
        bool vSync{};
    };

    class SettingsManager
    {
    public:
        SettingsManager();

        void load(const std::string& path);
        void save(const std::string& path) const;

        Settings& settings();
        const Settings& settings() const;

        void resetToDefault();

    private:
        Settings settings_;
    };
}
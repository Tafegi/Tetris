#pragma once

#include <string>
#include <memory>

namespace interfaces
{
    class IResourceProvider
    {
    public:
        virtual ~IResourceProvider() = default;

        virtual void loadTexture(const std::string& id, const std::string& path) = 0;
        virtual void loadFont(const std::string& id, const std::string& path) = 0;

        virtual void loadSound(const std::string& id, const std::string& path) = 0;
    };
}
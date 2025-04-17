#ifndef __SPRITE__
    #define __SPRITE__

#include "../transform/Transform.hpp"

#include <string>

class Sprite {
    public:
        Sprite() = default;
        Sprite(const std::string &assetPath);
        Sprite(const Sprite &other);
        void setAssetPath(const std::string &assetPath);
        const std::string &getAssetPath() const;
        Transform &getTransform();
        const Transform &getTransform() const;
        void operator=(const Sprite &other);
    private:
        std::string _assetPath;
        Transform _transform;
};

#endif

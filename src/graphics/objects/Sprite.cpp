#include "Sprite.hpp"

Sprite::Sprite(const std::string &assetPath) : _assetPath(assetPath) {}

Sprite::Sprite(const Sprite &other)
{
    _assetPath = other._assetPath;
    _transform = other._transform;
}

void Sprite::setAssetPath(const std::string &assetPath)
{
    _assetPath = assetPath;
}

const std::string &Sprite::getAssetPath() const
{
    return _assetPath;
}

Transform &Sprite::getTransform()
{
    return _transform;
}

const Transform &Sprite::getTransform() const
{
    return _transform;
}

void Sprite::operator=(const Sprite &other)
{
    _assetPath = other._assetPath;
    _transform = other._transform;
}

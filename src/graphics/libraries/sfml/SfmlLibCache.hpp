#ifndef __SFML_LIB_CACHE__
    #define __SFML_LIB_CACHE__

#include "../../cache/CacheManager.hpp"
#include <memory>
#include <SFML/Graphics.hpp>
#include "../../../error/Error.hpp"
#include "../../../error/ErrorMessages.hpp"
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Window/Keyboard.hpp>

class SfmlLibCache : public CacheManager<std::shared_ptr<sf::Texture>, sf::Font> {
    public:
        SfmlLibCache() = default;
        ~SfmlLibCache() = default;
        std::shared_ptr<sf::Texture> createSprite(const Sprite &sp) override;
        sf::Font createFont(const Text &f) override;
        void deleteSprite(std::shared_ptr<sf::Texture> sprite) override;
        void deleteFont(sf::Font font) override;
};

inline std::shared_ptr<sf::Texture> SfmlLibCache::createSprite(const Sprite &sp)
{
    auto assetPath = sp.getAssetPath() + ".png";
    
    auto texture = std::make_shared<sf::Texture>();
    if (!texture->loadFromFile(assetPath)) {
        throw GraphicLibraryError(Graphic::messages.find(Graphic::SPRITE_NOT_LOAD)->second);
    }
    return texture;
}

inline sf::Font SfmlLibCache::createFont(const Text &f)
{
    sf::Font font;
    auto fontPath = f.getFontPath();

    if (!font.loadFromFile(fontPath)) {
        throw GraphicLibraryError(Graphic::messages.find(Graphic::TEXT_NOT_LOAD)->second);
    }
    return font;
}

inline void SfmlLibCache::deleteFont(sf::Font font)
{
    (void)font;
    // TODO:
}

inline void SfmlLibCache::deleteSprite(std::shared_ptr<sf::Texture> sprite)
{
    (void)sprite;
    // TODO:
}

#endif

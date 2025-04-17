#ifndef __CACHE_MANAGER__
    #define __CACHE_MANAGER__

#include <map>
#include <string>
#include "../../graphics/objects/Sprite.hpp"
#include "../../graphics/objects/Text.hpp"

template<typename S, typename F>
class CacheManager {
    public:
        CacheManager() = default;
        ~CacheManager() = default;
        S cacheSprite(const Sprite &sp);
        F cacheFont(const Text &f);
        void clearCahce();
    protected:
        virtual S createSprite(const Sprite &sp) = 0;
        virtual F createFont(const Text &f) = 0;
        virtual void deleteFont(F font) = 0;
        virtual void deleteSprite(S sprite) = 0;
    private:
        std::map<std::string, S> _spriteCache;
        std::map<std::string, F> _fontCache;
};

template<typename S, typename F>
S CacheManager<S, F>::cacheSprite(const Sprite &sp)
{
    auto assetPath = sp.getAssetPath();

    if (_spriteCache.contains(assetPath)) {
        return _spriteCache[assetPath];
    }
    S sprite = this->createSprite(sp);
    _spriteCache[assetPath] = sprite;
    return sprite;
}

template<typename S, typename F>
F CacheManager<S, F>::cacheFont(const Text &f)
{
    auto fontPath= f.getFontPath();

    if (_fontCache.contains(fontPath)) {
        return _fontCache[fontPath];
    }
    F font = this->createFont(f);
    _fontCache[fontPath] = font;
    return font;
}

template<typename S, typename F>
void CacheManager<S, F>::clearCahce()
{
    _spriteCache.clear();
    _fontCache.clear();
}

#endif

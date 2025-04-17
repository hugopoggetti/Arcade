#pragma once

#include "../../cache/CacheManager.hpp"

class NcurseLibCache : public CacheManager<char, char> {
    public:
        NcurseLibCache() = default;
        ~NcurseLibCache() = default;
        char getNcurseTsprite(const std::string& assetsPath);
    protected:
        char createSprite
            (const Sprite &sp) override;
        char createFont
            (const Text &f) override;
        void deleteSprite(char a) override;
        void deleteFont(char a) override;
    private:
};

inline char NcurseLibCache::createSprite(const Sprite &sp)
{
    return getNcurseTsprite(sp.getAssetPath() + ".txt");
}

inline char NcurseLibCache::createFont(const Text &f)
{
    return getNcurseTsprite(f.getFontPath() + ".txt");
}

inline void NcurseLibCache::deleteSprite(char a) { (void)a; }

inline void NcurseLibCache::deleteFont(char a) { (void)a; }

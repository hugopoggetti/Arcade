#include "NcurseLibCache.hpp"
#include <fstream>

char NcurseLibCache::getNcurseTsprite(const std::string &assetPath)
{
    std::ifstream file(assetPath);

    if (!file) 
        return '?';

    char Tsprite = 0;

    file.get(Tsprite);
    file.close();

    return (file) ? Tsprite : '?';
}


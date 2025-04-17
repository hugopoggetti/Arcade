#ifndef __MODULE_MANAGER__
    #define __MODULE_MANAGER__

#include "Loader.hpp"

#include "../graphics/IDisplayModule.hpp"
#include "../games/IGameModule.hpp"

#include <vector>
#include <memory>
#include <filesystem>

#define GRAPHIC_MODULE_CONSTRUCTOR "getGraphics"
#define GAME_MODULE_CONSTRUCTOR "getGame"

namespace Module
{
    class ModuleManager {
        public:
            ModuleManager() = default;
            ~ModuleManager();
            void load(const std::filesystem::path &modulePath);
            void unloadGraphics();
            void unloadGames();
            const std::vector<IDisplayModule *> &getGraphicsModules() const;
            const std::vector<IGameModule *> &getGamesModules() const;
            const std::vector<std::string> &getGamesmodulesPath() const;
            const std::vector<std::string> &getGraphicsmodulesPath() const;
        private:
            std::vector<Loader> _loaders;
            std::vector<IDisplayModule *> _graphicsModules;
            std::vector<IGameModule *> _gamesModules;
            std::vector<std::string> _graphicsModulesPath;
            std::vector<std::string> _gamesModulesPath;
    };
}

#endif

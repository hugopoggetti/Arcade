#ifndef __CORE__
    #define __CORE__

#include <filesystem>
#include <vector>
#include <queue>
#include "../error/Error.hpp"
#include "../error/ErrorMessages.hpp"
#include "../loader/ModuleManager.hpp"
#include "EventManager.hpp"
#include "../games/IGameModule.hpp"
#include <algorithm>

#define LIB_PATH "./lib/"

namespace Arcade
{
    class Core {
        public:
            Core() = default;
            Core(const std::string &libPath);
            ~Core() = default;
            void read(const std::string &libPath);
            const std::vector<std::filesystem::path> &getLibraries() const;
            void setGamesPath(const std::vector<std::string> &GamesPaths);
            void setGraphicsPath(const std::vector<std::string> &GraphicsPaths);
            void CoreLoop(const std::string &lib);
            std::vector<std::string> removeDuplicates(std::vector<std::string> vec);
            IGameModule *getCurrentGame() const;
            IDisplayModule *getCurrentDisplay() const;
            void setCurrentGame(IGameModule *game);
            void setCurrentDisplay(IDisplayModule *dsp);
            bool isRunning() const;
            void setRunning(bool run);
            const std::vector<std::string> &getGamesPath() const;
            const std::vector<std::string> &getGraphicsPath() const;
        private:
            std::vector<std::filesystem::path> _libraries;
            IGameModule *CurrentGame = nullptr;
            IDisplayModule *CurrentDisplay = nullptr;
            bool _running = true;
            std::vector<std::string> _gamesPath;
            std::vector<std::string> _graphicsPath;
    };
}

#endif

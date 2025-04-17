#include "core/Core.hpp"
#include "loader/ModuleManager.hpp"
#include "error/Error.hpp"
#include "error/ErrorMessages.hpp"

#include <iostream>

int main(int argc, const char **argv)
{
    if (argc != 2) {
        std::cerr << Arcade::messages.find(Arcade::BAD_NUMBER_ARGUMENTS)->second << std::endl;
        return 84;
    }
    Arcade::Core core;
    try {
        core.read(LIB_PATH);
    } catch (Arcade::ErrorCore &e) {
        std::cerr << e.what() << std::endl;
        return 84;
    }
    Module::ModuleManager moduleManager;
    try {
        moduleManager.load(argv[1]);
        if (moduleManager.getGraphicsModules().empty()) {
            std::cerr << Module::messages.find(Module::FIRST_MODULE_NOT_GRAPHIC)->second << std::endl;
            return 84;
        }
        for (auto it = core.getLibraries().begin(); it != core.getLibraries().end(); ++it) {
            moduleManager.load((*it));
        }
        moduleManager.unloadGames();
        moduleManager.unloadGraphics();
    } catch (Module::ErrorLoader &e) {
        std::cerr << e.what() << std::endl;
        return 84;
    } catch (Module::ErrorModule &e) {
        std::cerr << e.what() << std::endl;
        return 84;
    }
    // set avaibles games
    core.setGraphicsPath(moduleManager.getGraphicsmodulesPath());
    core.setGamesPath(moduleManager.getGamesmodulesPath());
    // start game here !
    core.CoreLoop(argv[1]);
    return 0;
}

#include "ModuleManager.hpp"
#include "../error/Error.hpp"
#include "../error/ErrorMessages.hpp"

#include "../plugin/Plugin.hpp"

Module::ModuleManager::~ModuleManager()
{
    for (auto it = _loaders.begin(); it != _loaders.end(); ++it) {
        (*it).close();
    }
}

void Module::ModuleManager::load(const std::filesystem::path &modulePath)
{
    Module::Loader newModule;

   for (auto it = _loaders.begin(); it != _loaders.end(); ++it) {
        if ((*it).getModulePath() == modulePath) {
            return;
        }
    }
    newModule.open(modulePath);
    if (newModule.resolver(GRAPHIC_MODULE_CONSTRUCTOR) != nullptr) {
        // generate constructor IDisplayModule 
        IDisplayModule *(*graphicModuleConstructor)() = nullptr;
        *(void **) (&graphicModuleConstructor) = newModule.resolver(GRAPHIC_MODULE_CONSTRUCTOR);
            IDisplayModule *graphicModule = graphicModuleConstructor();
            _graphicsModules.push_back(graphicModule);
            _graphicsModulesPath.push_back(modulePath);
            _loaders.push_back(newModule);
            return;
    } 
    if (newModule.resolver(GAME_MODULE_CONSTRUCTOR) != nullptr) {
        // generate constructor IGameModule
        IGameModule *(*gameModuleConstructor)() = nullptr;
        *(void **) (&gameModuleConstructor) = newModule.resolver(GAME_MODULE_CONSTRUCTOR);
            IGameModule * gameModule = gameModuleConstructor();
            _gamesModules.push_back(gameModule);
            _gamesModulesPath.push_back(modulePath);
            _loaders.push_back(newModule);
            return;
    } 
    throw ErrorModule(messages.find(MODULE_NOT_VALID)->second);
}

void Module::ModuleManager::unloadGames()
{
    // for (auto &it : _gamesModules)
    //     delete it;
    _gamesModules.clear();
}

void Module::ModuleManager::unloadGraphics()
{
    // for (auto &it : _gamesModules)
    //     delete it;
    _graphicsModules.clear();
}

const std::vector<IDisplayModule *> &Module::ModuleManager::getGraphicsModules() const
{
    return _graphicsModules;
}

const std::vector<IGameModule *> &Module::ModuleManager::getGamesModules() const
{
    return _gamesModules;
}

const std::vector<std::string> &Module::ModuleManager::getGraphicsmodulesPath() const
{
    return _graphicsModulesPath;
}

const std::vector<std::string> &Module::ModuleManager::getGamesmodulesPath() const
{
    return _gamesModulesPath;
}

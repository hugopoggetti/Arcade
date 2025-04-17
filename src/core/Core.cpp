#include "Core.hpp"
#include "menu/Menu.hpp"
#include <x86gprintrin.h>

Arcade::Core::Core(const std::string &libPath)
{
    std::filesystem::path path = libPath;

    if (!std::filesystem::exists(path) && !std::filesystem::is_directory(path)) {
        throw ErrorCore(messages.find(NOT_FOUND_LIB)->second);
    }
    for (auto it : std::filesystem::directory_iterator(path)) {
        std::filesystem::path element = it;
        if (!element.has_extension() && element.extension() != ".so") {
            throw ErrorCore(messages.find(NOT_SHARED_LIBRARY)->second);
        }
        _libraries.push_back(element);
    }
}

void Arcade::Core::read(const std::string &libPath)
{
    std::filesystem::path path = libPath;

    if (!std::filesystem::exists(path) && !std::filesystem::is_directory(path)) {
        throw ErrorCore(messages.find(NOT_FOUND_LIB)->second);
    }
    for (auto it : std::filesystem::directory_iterator(path)) {
        std::filesystem::path element = it;
        if (!element.has_extension() && element.extension() != ".so") {
            throw ErrorCore(messages.find(NOT_SHARED_LIBRARY)->second);
        }
        _libraries.push_back(element);
    }
}

std::vector<std::string> Arcade::Core::removeDuplicates(std::vector<std::string> vec)
{
    vec.erase(
        std::remove_if(vec.begin(), vec.end(), [](const std::string &s) {
            return !s.empty() && s[0] != '.';
        }),
        vec.end()
    );
    std::sort(vec.begin(), vec.end());
    vec.erase(std::unique(vec.begin(), vec.end()), vec.end());
    return vec;
}

const std::vector<std::filesystem::path> &Arcade::Core::getLibraries() const
{
    return _libraries;
}

void Arcade::Core::setGamesPath(const std::vector<std::string> &gamePath)
{
    _gamesPath = removeDuplicates(gamePath);
}

void Arcade::Core::setGraphicsPath(const std::vector<std::string> &GraphicPath)
{
    _graphicsPath = removeDuplicates(GraphicPath); 
}

IGameModule *Arcade::Core::getCurrentGame() const
{
    return CurrentGame;
}

IDisplayModule *Arcade::Core::getCurrentDisplay() const
{
    return CurrentDisplay;
}

void Arcade::Core::setCurrentGame(IGameModule *game)
{
   CurrentGame = game; 
}

void Arcade::Core::setCurrentDisplay(IDisplayModule *dsp)
{
    CurrentDisplay = dsp;
}

bool Arcade::Core::isRunning() const
{
    return (_running);
}

void Arcade::Core::setRunning(bool run)
{
    _running = run;
}

const std::vector<std::string> &Arcade::Core::getGamesPath() const
{
    return _gamesPath;
}
const std::vector<std::string> &Arcade::Core::getGraphicsPath() const
{
    return _graphicsPath;
}

void Arcade::Core::CoreLoop(const std::string &lib)
{
    Module::ModuleManager moduleManager;
    EventManager eventManager; 
    moduleManager.load(lib);
    
    if (moduleManager.getGraphicsModules().empty())
        return;

    CurrentDisplay =  moduleManager.getGraphicsModules()[0];
    CurrentDisplay->init(1920, 1080);
    
    IGameModule *menu = new Menu(*this, moduleManager, eventManager);
    menu->init();

    eventManager.registerGuiListeners(menu);
    while (_running)
    {
        eventManager.pollEvents(CurrentDisplay);
        eventManager.transmitEvents(menu, CurrentGame);

        // check quit event 
        if (!_running)
            return;
        // display 
        CurrentDisplay->clear();
        menu->run(*CurrentDisplay);
        CurrentDisplay->display();
    }
    return;
}

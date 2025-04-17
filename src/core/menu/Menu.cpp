#include "Menu.hpp"
#include <iterator>
#include <iostream>
#include "../score/HighScoreManager.hpp"

Menu::Menu(Arcade::Core &core,
        Module::ModuleManager &modulemanager, EventManager &EventManager)
    : _core(core), _modulemanager(modulemanager), _handleEvents(EventManager) {}

Menu::~Menu() {}

void Menu::init()
{
    _core.getCurrentDisplay()->setColorPalette(getColorPalette());
    _core.getCurrentDisplay()->
        setGridSize(getGridSize().first, getGridSize().second);
    _core.getCurrentDisplay()->setWindowSize(1920, 1080);
}

std::pair<std::size_t, std::size_t> Menu::getGridSize()
{
    return {100,50};
}
    
std::map<Color::ColorID, Color::color_t> Menu::getColorPalette()
{
    return _colorPalette;
}

void Menu::run(IDisplayModule &dsp)
{
    if (!_core.isRunning())
        return;
    _dsp = &dsp;
    if (!_launch) {
        displayMenu();
    } else if (_core.getCurrentGame() != nullptr){
        _core.getCurrentGame()->run(dsp);
    }
}

void Menu::stop()
{
    if (_core.getCurrentGame() != nullptr) {
        HighScoreManager scoreManager(_core.getCurrentGame()->getPlugin().getName(), _core.getCurrentGame()->getScore());
        scoreManager.encryptScore();
    }
    _core.setRunning(false);
    _dsp->destroy();
}

std::vector<Listener *> &Menu::getGameListeners()
{
    _listener.push_back({&_events});
    return _listener;
}

int Menu::getScore() const
{
    return 0;
}

void Menu::setBestScore(int score)
{
    (void)score;    
}

void Menu::nextGraphic()
{
    _GraphicIndex++;
    if (_GraphicIndex >= (int)_core.getGraphicsPath().size())
        _GraphicIndex = 0;
    _dsp->destroy();
    _modulemanager.unloadGraphics();
    _modulemanager.load(_core.getGraphicsPath()[_GraphicIndex]);
    _core.setCurrentDisplay(_modulemanager.getGraphicsModules()[0]);
    _core.getCurrentDisplay()->init(1920, 1080);
    _dsp = _core.getCurrentDisplay();
    init();
    if (_core.getCurrentGame()) {
        initGame();
    }
}

void Menu::prevGraphic()
{
    _GraphicIndex--;
    if (_GraphicIndex < 0)
        _GraphicIndex = (int)_core.getGraphicsPath().size() - 1;
    _dsp->destroy();
    _modulemanager.unloadGraphics();
    _modulemanager.load(_core.getGraphicsPath()[_GraphicIndex]);
    _core.setCurrentDisplay(_modulemanager.getGraphicsModules()[0]);
    _core.getCurrentDisplay()->init(1920, 1080);
    _dsp = _core.getCurrentDisplay();
    init();
    if (_core.getCurrentGame()) {
        initGame();
    }
}

void Menu::selectGame(bool up)
{
    int limit = (int)_core.getGamesPath().size();
    if (up) {
        _SelectGame--;
        if (_SelectGame < 0)
            _SelectGame = limit - 1;
    } else {
        _SelectGame++;
        if (_SelectGame >= limit)
            _SelectGame = 0;
    }
}

void Menu::selctGraphic(bool up)
{
    int limit = (int)_core.getGraphicsPath().size();
    if (up) {
        _SelectGraphic--;
        if (_SelectGraphic < 0)
            _SelectGraphic = limit - 1;
    } else {
        _SelectGraphic++;
        if (_SelectGraphic >= limit)
            _SelectGraphic = 0;
    }
}

void Menu::initGame()
{
    _core.getCurrentDisplay()->
        setColorPalette(_core.getCurrentGame()->getColorPalette());
    _core.getCurrentDisplay()->setGridSize(
        _core.getCurrentGame()->getGridSize().first,
        _core.getCurrentGame()->getGridSize().second);
}

void Menu::starGame()
{
    _dsp->destroy();
    _modulemanager.unloadGraphics();
    _modulemanager.load(_core.getGraphicsPath()[_SelectGraphic]);
    _core.setCurrentDisplay(_modulemanager.getGraphicsModules()[0]);
    _core.getCurrentDisplay()->init(1920, 1080);
    _dsp = _core.getCurrentDisplay();
    init();
    if (_core.getGamesPath().empty())
        return;
    _modulemanager.load(_core.getGamesPath()[_SelectGame]);
    _core.setCurrentGame(_modulemanager.getGamesModules()[0]);
    _handleEvents.registerGameListeners(_core.getCurrentGame());
    initGame();
    _core.getCurrentGame()->init();
    HighScoreManager scoreManager(_core.getCurrentGame()->getPlugin().getName(), 0);
    _core.getCurrentGame()->setBestScore(scoreManager.getBestScore());
    _launch = true;
}

void Menu::backToMenu()
{
    if (_core.getCurrentGame() != nullptr) {
        HighScoreManager scoreManager(_core.getCurrentGame()->getPlugin().getName(), _core.getCurrentGame()->getScore());
        scoreManager.encryptScore();
    }
    _core.setCurrentGame(nullptr);
    _modulemanager.unloadGames();
    init();
    _SelectGame = 0;
    _SelectGraphic = 0;
    _launch = false;
}

void Menu::nextGame()
{
    _SelectGame++;
    if (_SelectGame >= (int)_core.getGamesPath().size())
        _SelectGame = 0;
    _core.setCurrentGame(nullptr);
    _modulemanager.unloadGames();
    _modulemanager.load(_core.getGamesPath()[_SelectGame]);
    _core.setCurrentGame(_modulemanager.getGamesModules()[0]);
    _handleEvents.registerGameListeners(_core.getCurrentGame());
    initGame();
    _core.getCurrentGame()->init();
    HighScoreManager scoreManager(_core.getCurrentGame()->getPlugin().getName(), 0);
    _core.getCurrentGame()->setBestScore(scoreManager.getBestScore());
}

const Plugin &Menu::getPlugin() const
{
    static Plugin plugin;
    return plugin;
}

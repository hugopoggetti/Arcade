#pragma once

#include "../Core.hpp"
#include <cstdlib>
#include "MenuEvents.hpp"

class Menu : public IGameModule {
    public:
        Menu(Arcade::Core &core,
                Module::ModuleManager& modulemanager,
                EventManager &_handleEvents);
        ~Menu();
        void init() override;
        void run(IDisplayModule &dsp) override;
        std::pair<std::size_t, std::size_t> getGridSize() override;
        std::map<Color::ColorID, Color::color_t> getColorPalette() override;
        std::vector<Listener *> &getGameListeners() override;
        int getScore() const override;
        void setBestScore(int score) override;
        const Plugin &getPlugin() const override;
        void nextGraphic();
        void prevGraphic();
        void selectGame(bool up);
        void selctGraphic(bool up);
        void starGame();
        void displayMenu();
        void backToMenu();
        void nextGame();
        void stop();
    private:
        Arcade::Core &_core;
        Module::ModuleManager& _modulemanager;
        std::vector<Listener *> _listener;
        EventManager &_handleEvents; 
        MenuEvents _events;
        IDisplayModule *_dsp;
        int _GameIndex = 0;
        int _GraphicIndex = 0;
        int _SelectGame = 0;
        int _SelectGraphic = 0;
        bool _launch = false;
        const std::map<Color::ColorID, Color::color_t> _colorPalette = {
            { Color::ColorID::BLUE,   {0, 0, 255, 255} },
            { Color::ColorID::RED,    {255, 0, 0, 255} },
            { Color::ColorID::BLACK,  {0, 0, 0, 255} },
            { Color::ColorID::WHITE,  {255, 255, 255, 255} },
            { Color::ColorID::GREEN,  {0, 255, 0, 255} },
            { Color::ColorID::YELLOW, {255, 255, 0, 255} },
            { Color::ColorID::PURPLE, {128, 0, 128, 255} },
            { Color::ColorID::ORANGE, {255, 165, 0, 255} }
        };
        // display menu
        void initGame();
        void displayLib(Text &text);
        void displayTitle(Text &text);
        void displaySelectedItem(Text &text);
        void displayBorder(Rectangle &rectangle);
};

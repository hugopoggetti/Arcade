#pragma once

#include "../IGameModule.hpp"
#include "../../core/EventManager.hpp"
#include "SnakeEvents.hpp"
#include "Wall.hpp"
#include "Food.hpp"

class Snake : public IGameModule {
    public:
        Snake();
        ~Snake();
        void init() override;
        void run(IDisplayModule &dsp) override;
        std::pair<std::size_t, std::size_t> getGridSize() override;
        std::map<Color::ColorID, Color::color_t> getColorPalette() override;
        std::vector<Listener *> &getGameListeners() override;
        int getScore() const override;
        void setBestScore(int score) override;
        const Plugin &getPlugin() const override;
        void reset(bool live);
        void speedUp();
    private:
        std::vector<Listener *> _listener;
        Plugin _plugin;
        // game utils
        // snake game methods
        void changeDirection(Direction direction);
        void initSnakeWindow();
        void getNewDirection();
        void die();
        void moveSnake();
        bool checkCollision(std::pair<int, int> pos);
        void drawGame(IDisplayModule &dsp);
        void drawSnake(IDisplayModule &dsp);
        void drawGameInfo(IDisplayModule &dsp);
        void displayGameOver(IDisplayModule &dsp);
        std::deque<std::pair<int, int>> _snake;
        Direction _direction = S_RIGHT;
        int _lives = 3;
        int _score = 0;
        int _bestScore = 0;
        bool _initialized = false;
        bool _gameover = false;
        int _speed = 0;
        SnakeEvents _events;
        Wall wall;
        Food _food;
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
};



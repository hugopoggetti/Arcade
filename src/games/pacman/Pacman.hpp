#pragma once

#include "../IGameModule.hpp"
#include "Map.hpp"
#include "PacmanEvent.hpp"

struct Ghost {
    int x;
    int y;
    Element underTile;
};

enum Direction { UN, P_UP, P_DO, P_LE, P_RI };

class Pacman : public IGameModule {
    public:
        Pacman();
        ~Pacman();
        void init() override;
        void run(IDisplayModule &dsp) override;
        std::pair<std::size_t, std::size_t> getGridSize() override;
        std::map<Color::ColorID, Color::color_t> getColorPalette() override;
        std::vector<Listener *> &getGameListeners()override;
        int getScore() const override;
        void setBestScore(int score) override;
        const Plugin &getPlugin() const override;
        void moveUp();
        void moveDown();
        void moveLeft();
        void moveRight();
    private:
        void move();
        void moveMob();
        void displayScore();
        IDisplayModule *_dsp;
        std::vector<Listener *> _listener;
        PacmanEvents _evts;
        Map _mapHelper;
        Direction _direction = UN;
        std::vector<std::vector<Element>> _map;
        std::vector<std::vector<Element>> _backgroundMap;
        std::vector<Ghost> _ghosts;
        int _score = 0;
        int _bestScore = 0;
        int _lives = 3;
        void respawnPacman();
};

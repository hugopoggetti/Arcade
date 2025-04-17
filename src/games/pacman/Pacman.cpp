#include "Pacman.hpp"
#include <iostream>
#include <chrono>
#include <string>
#include <thread>

Pacman::Pacman() {}
Pacman::~Pacman() {}

void Pacman::init()
{
    _map = _mapHelper.getMap();
    _backgroundMap = _map;
    _ghosts.clear();
    _score = 0;
    _lives = 3;
    _direction = UN;

    for (std::size_t y = 0; y < _map.size(); ++y) {
        for (std::size_t x = 0; x < _map[y].size(); ++x) {
            if (_map[y][x] == _I) {
                Ghost ghost;
                ghost.x = static_cast<int>(x);
                ghost.y = static_cast<int>(y);
                ghost.underTile = _P;
                _ghosts.push_back(ghost);
            }
        }
    }
}

void Pacman::run(IDisplayModule &dsp)
{
    _dsp = &dsp;
    _dsp->setGridSize(70, 35);
    _mapHelper.displayMap(25, 7, _map, _dsp);
    moveMob();
    move();
    displayScore();
    std::this_thread::sleep_for(std::chrono::milliseconds(200));
}

std::vector<Listener *> &Pacman::getGameListeners()
{
    _listener.push_back({&_evts});
    return _listener;
}

int Pacman::getScore() const { return _bestScore; }

void Pacman::setBestScore(int score) { _bestScore = score; }

const Plugin &Pacman::getPlugin() const
{
    static Plugin plugin;
    return plugin;
}

void Pacman::moveUp() { _direction = P_UP; }
void Pacman::moveDown() { _direction = P_DO; }
void Pacman::moveLeft() { _direction = P_LE; }
void Pacman::moveRight() { _direction = P_RI; }

std::map<Color::ColorID, Color::color_t> Pacman::getColorPalette()
{
    std::map<Color::ColorID, Color::color_t> colorPalette;

    colorPalette[Color::BACKGROUND] = { 0, 0, 0, 255 };
    colorPalette[Color::TRANSPARENT] = { 0, 0, 0, 0 };
    colorPalette[Color::BLUE] = { 0, 0, 255, 255 };
    colorPalette[Color::RED] = { 255, 0, 0, 255 };
    colorPalette[Color::BLACK] = { 0, 0, 0, 255 };
    colorPalette[Color::WHITE] = { 255, 255, 255, 255 };
    colorPalette[Color::GREEN] = { 0, 255, 0, 255 };
    colorPalette[Color::YELLOW] = { 255, 255, 0, 255 };
    colorPalette[Color::PURPLE] = { 128, 0, 128, 255 };
    colorPalette[Color::ORANGE] = { 255, 165, 0, 255 };

    return colorPalette;
}

void Pacman::move()
{
    int x = -1, y = -1;
    for (std::size_t i = 0; i < _map.size(); ++i) {
        for (std::size_t j = 0; j < _map[i].size(); ++j) {
            if (_map[i][j] == _G) {
                y = (int)i;
                x = (int)j;
                break;
            }
        }
        if (x != -1) break;
    }

    if (x == -1 || y == -1)
        return;

    int newX = x, newY = y;

    switch (_direction) {
        case P_UP: newY -= 1; break;
        case P_DO: newY += 1; break;
        case P_LE: newX -= 1; break;
        case P_RI: newX += 1; break;
        default: return;
    }

    if (newY < 0 || newY >= (int)_map.size() || newX < 0 || newX >= (int)_map[0].size())
        return;

    if (newY == 9) {
        if (newX == 0) newX = 18;
        else if (newX == 18) newX = 0;
    }

    if (_map[newY][newX] != _M) {
        if (_map[newY][newX] == _P) {
            _score += 10;
            if (_score > _bestScore) _bestScore = _score;
        } else if (_map[newY][newX] == _W) {
            _score += 100;
            if (_score > _bestScore) _bestScore = _score;
        }

        if (_map[newY][newX] == _I) {
            _lives--;
            _map[y][x] = _V;
            respawnPacman();
            return;
        }

        _map[y][x] = _V;
        _map[newY][newX] = _G;
    }
}

void Pacman::respawnPacman()
{
    if (_lives <= 0) {
        init();
        return;
    }

    bool pacmanRespawned = false;

    for (int r = 11; r <= 13; ++r) {
        for (int c = 8; c <= 10; ++c) {
            if (_map[r][c] == _P || _map[r][c] == _V) {
                _map[r][c] = _G;
                pacmanRespawned = true;
                break;
            }
        }
        if (pacmanRespawned) break;
    }
}

void Pacman::moveMob()
{
    bool pacmanEaten = false;
    int pacmanX = -1, pacmanY = -1;

    for (std::size_t i = 0; i < _map.size(); ++i) {
        for (std::size_t j = 0; j < _map[i].size(); ++j) {
            if (_map[i][j] == _G) {
                pacmanY = static_cast<int>(i);
                pacmanX = static_cast<int>(j);
                break;
            }
        }
        if (pacmanX != -1) break;
    }

    for (auto& ghost : _ghosts) {
        _map[ghost.y][ghost.x] = ghost.underTile;

        int newX = ghost.x;
        int newY = ghost.y;
        int dir = rand() % 4;
        
        switch (dir) {
            case 0: newY -= 1; break;
            case 1: newY += 1; break;
            case 2: newX -= 1; break;
            case 3: newX += 1; break;
        }

        if (newY < 0 || newY >= (int)_map.size() || newX < 0 || newX >= (int)_map[0].size()) {
            newX = ghost.x;
            newY = ghost.y;
        }

        Element target = _map[newY][newX];

        if (target == _M || target == _I) {
            newX = ghost.x;
            newY = ghost.y;
        }

        if (target == _G) {
            pacmanEaten = true;
        }

        ghost.underTile = _map[newY][newX];
        ghost.x = newX;
        ghost.y = newY;
        _map[newY][newX] = _I;
    }

    if (pacmanEaten) {
        _lives--;

        if (pacmanX != -1 && pacmanY != -1) {
            _map[pacmanY][pacmanX] = _V;
        }

        respawnPacman();
    }
}

void Pacman::displayScore()
{
    std::string score = "Score  " + std::to_string(_score);
    std::string lives = "Lives  " + std::to_string(_lives);
    std::string best = "Best Score  " + std::to_string(_bestScore);

    Text text;
    text.setFontPath("./assets/font/Popstar.ttf");
    text.setColor(Color::ColorID::BLUE);
    text.getTransform().getSize().setPosition(1, 1);
    text.getTransform().getPosition().setPosition(15, 4);
    text.setText(score);
    _dsp->draw(text);

    text.getTransform().getPosition().setPosition(30, 4);
    text.setText(lives);
    _dsp->draw(text);

    text.getTransform().getPosition().setPosition(45, 4);
    text.setText(best);
    _dsp->draw(text);
}

std::pair<std::size_t, std::size_t> Pacman::getGridSize()
{
    return {70, 35};
}

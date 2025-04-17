#include "Minesweeper.hpp"
#include <cmath>
#include <iostream>
#include <memory>
#include <pthread.h>
#include <random>
#include <string>

MineSweeper::MineSweeper() : _plugin("MineSweeper", "1.0", "t", "") {}

MineSweeper::~MineSweeper() {}

void MineSweeper::init()
{
    _cels.resize(ROWS);
    for (int i = 0; i < ROWS; i++) {
        _cels[i].resize(COLS);
    }
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS ;j++) {
            _cels[i][j] = std::make_unique<Cell>(i,j,0);
        }
    }
    _timer.reset(120);
    initSprites();
}

void MineSweeper::reset(bool reset)
{
    if (_gameOver || reset) {
        init();
        _score = 0;
        _gameOver = false;
        _open = false;
        _validFlag = 0;
    }
}

void MineSweeper::initSprites()
{
    const std::vector<std::string> paths = {
        "flag", "1", "2", "3", "4", "5", "6", "7", "8", "0", "bomb"
    };
    _sprites.resize(11);
    for (size_t i = 0; i < paths.size(); ++i) {
        _sprites[i] = std::make_unique<Sprite>("./assets/sweeper/" + paths[i]);
    }
}

void MineSweeper::generateMines(Position pos)
{    
    std::random_device rd;
    std::mt19937 random_engine(rd());
    bool validGrid = false;

    while (!validGrid) {
        for (int x = 0; x < COLS; ++x)
            for (int y = 0; y < ROWS; ++y)
                _cels[x][y]->setMine(false);

        std::vector<std::pair<int, int>> possiblePositions;

        for (int x = 0; x < COLS; ++x) {
            for (int y = 0; y < ROWS; ++y) {
                if (std::abs(x - pos.getX()) <= 1 && std::abs(y - pos.getY()) <= 1)
                    continue;
                possiblePositions.emplace_back(x, y);
            }
        }
        std::shuffle(possiblePositions.begin(), possiblePositions.end(), random_engine);

        for (unsigned short i = 0; i < MINES; ++i) {
            auto [mx, my] = possiblePositions[i];
            _cels[mx][my]->setMine(true);
        }
        for (int x = 0; x < COLS; ++x)
            for (int y = 0; y < ROWS; ++y)
                _cels[x][y]->countMineAround(_cels);

        if (_cels[(int)pos.getX()][(int)pos.getY()]->getMineAround() == 0)
            validGrid = true;
    }
}

std::pair<std::size_t, std::size_t> MineSweeper::getGridSize()
{
    return {ROWS, COLS + 2};
}

std::map<Color::ColorID, Color::color_t> MineSweeper::getColorPalette()
{
    return _colorPalette;
}

 void MineSweeper::run(IDisplayModule &dsp)
{
    dsp.setWindowSize(600, 600);
    displayGrid(dsp);
    displayScore(dsp);
    if (_timer.isFinished())
        _gameOver = true;
}

void MineSweeper::displayGrid(IDisplayModule &dsp)
{
    Rectangle rect;
    rect.fillRect(1);
    rect.getTransform().getSize().setPosition(0.8,0.8) ;
    for (std::size_t i = 0; i < _cels.size(); i++) {
        for (std::size_t j = 0; j < _cels[i].size() ;j++) {
            if (_gameOver && _cels[i][j]->isMine()) {
                _sprites[10]
                    ->getTransform().getSize().setPosition(0.8, 0.8);
                _sprites[10]
                    ->getTransform().getPosition().setPosition((double)i, (double)j);
                dsp.draw(*_sprites[10]);
                continue;
            }
            if (_events.getMousePos().getX() >= (double) i
                    && _events.getMousePos().getX() <= (double)i + 1
                    && _events.getMousePos().getY() >= (double)j
                    && _events.getMousePos().getY() <= (double)j + 1
                    && !_cels[i][j]->getMarked() && _cels[i][j]->isHiden()) {
                rect.getTransform().getPosition().setPosition((double)i, (double)j);
                rect.setColor(Color::ColorID::PURPLE);
                dsp.draw(rect);
            } else if (!_cels[i][j]->isHiden() &&!_cels[i][j]->isMine()) {
                if (_cels[i][j]->getMineAround() >= 1) {
                    _sprites[_cels[i][j]->getMineAround()]
                        ->getTransform().getSize().setPosition(0.8, 0.8);
                    _sprites[_cels[i][j]->getMineAround()]
                        ->getTransform().getPosition().setPosition((double)i, (double)j);
                    dsp.draw(*_sprites[_cels[i][j]->getMineAround()]);
                } else {
                 _sprites[9]
                        ->getTransform().getSize().setPosition(0.8, 0.8);
                    _sprites[9]
                        ->getTransform().getPosition().setPosition((double)i, (double)j);
                    dsp.draw(*_sprites[9]);
                }
            } else if (_cels[i][j]->isHiden() && _cels[i][j]->getMarked()) {
                _sprites[0]->getTransform().getSize().setPosition(0.8, 0.8);
                _sprites[0]->getTransform().getPosition().setPosition((double)i, (double)j);
                dsp.draw(*_sprites[0]);
            } else {
                rect.getTransform().getPosition().setPosition((double)i, (double)j);
                rect.setColor(Color::ColorID::BLUE);
                dsp.draw(rect);
            }
        }
    }
}

void MineSweeper::displayScore(IDisplayModule &dsp)
{
    int remaining = _timer.remainingSeconds();
    int min = remaining / 60;
    int sec = remaining % 60;

    Text text;
    text.setFontPath("./assets/font/Popstar.ttf");
    text.setColor(Color::ColorID::BLUE);
    text.getTransform().getSize().setPosition(0.5, 0.5);
    if (!_gameOver) {
        if (_score >= _bestScore)
            _bestScore = _score;
        std::string score = "Score:  " +  std::to_string(_score);
        std::string best = "Best: " +  std::to_string(_bestScore);
        std::string timer = "Time " + std::to_string(min) + ":" + std::to_string(sec);
        std::string remainingFlag = "Remaining: " + std::to_string(MINES - _validFlag);
        text.getTransform().getPosition().setPosition(0, COLS);
        text.setText(score);
        dsp.draw(text);

        text.getTransform().getPosition().setPosition(3, COLS);
        text.setText(timer);
        dsp.draw(text);

        text.getTransform().getPosition().setPosition(6, COLS);
        text.setText(best);
        dsp.draw(text);

        text.getTransform().getPosition().setPosition(3, COLS + 1);
        text.setText(remainingFlag);
        dsp.draw(text);
    } else {
        text.getTransform().getPosition().setPosition(2, COLS);
        text.setText("Press Space to replay");
        dsp.draw(text);
    }
}

std::vector<Listener *> &MineSweeper::getGameListeners()
{
    _listener.push_back({&_events});
    return _listener;
}

int MineSweeper::getScore() const
{
    return _bestScore;
}

 void MineSweeper::setBestScore(int score)
{
    _bestScore = score;
}

const Plugin &MineSweeper::getPlugin() const
{
    return _plugin;
}

bool MineSweeper::victory()
{   
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS ;j++) {
            if (_cels[i][j]->isHiden() && !_cels[i][j]->isMine())
                return false;
        }
    }
    return true;
}

void MineSweeper::openCell(Position pos)
{
    if (!_gameOver) {
        if (pos.getX() >= 0 && pos.getX() <= ROWS && pos.getY() >= 0 && pos.getY() <= COLS) {
            if (!_open) {
               generateMines(pos);
               _open = true;
            }
            if (_cels[(int)pos.getX()][(int)pos.getY()]->open(_cels)) {
                // lose condition
                _gameOver = true;
            } else if (victory()) {
                _score += _timer.remainingSeconds();
                if (_score >= _bestScore)
                    _bestScore = _score;
                reset(1);
            }
        }
        if (!_gameOver)
            _score += _cels[(int)pos.getX()][(int)pos.getY()]->getMineAround() + 1;
    }
}

void MineSweeper::markCell(Position pos)
{
    if (!_gameOver) {
        if (pos.getX() >= 0 && pos.getX() <= ROWS && pos.getY() >= 0 && pos.getY() <= COLS) {
            if (_cels[(int)pos.getX()][(int)pos.getY()]->getMarked())
                _cels[(int)pos.getX()][(int)pos.getY()]->setMarked(0);
            else {
                if (_cels[(int)pos.getX()][(int)pos.getY()]->isMine()) {
                    _validFlag += 1;
                } else
                     _score -= 5;
                _cels[(int)pos.getX()][(int)pos.getY()]->setMarked(1);
            }
        }
    }
}

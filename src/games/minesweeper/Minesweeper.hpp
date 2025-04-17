#pragma once

#include "../IGameModule.hpp"
#include "MineSweeperEvents.hpp"
#include "MineSweeperTimer.hpp"
#include "MineSweeperCell.hpp"

class MineSweeper : public IGameModule {
    public:
        MineSweeper();
        ~MineSweeper();
        void init()  override;
        void run(IDisplayModule &dsp) override;
        std::pair<std::size_t, std::size_t> getGridSize() override;
        std::map<Color::ColorID, Color::color_t> getColorPalette() override;
        std::vector<Listener *> &getGameListeners()  override;
        int getScore() const  override;
        void setBestScore(int score)  override;
        const Plugin &getPlugin() const override;
        void markCell(Position pos);
        void openCell(Position pos);
        void reset(bool reset);
    private:
        std::vector<Listener *> _listener;
        Plugin _plugin;
        MineSweeperEvents _events;
        CountdownTimer _timer;
        // game utils
        const std::map<Color::ColorID, Color::color_t> _colorPalette = {
            { Color::ColorID::BLUE,   {0, 0, 255, 255} },
            { Color::ColorID::PURPLE, {30,144,255, 255} },
        };
        bool victory();
        void initSprites();
        void generateMines(Position pos);
        void displayGrid(IDisplayModule &dsp);
        void displayScore(IDisplayModule &dsp);
        std::vector<std::unique_ptr<Sprite>> _sprites;
        std::vector<std::vector<std::unique_ptr<Cell>>> _cels;
        int _score = 0;
        int _bestScore = 0;
        bool _gameOver = false;
        bool _open = false;
        int _validFlag = 0;
};

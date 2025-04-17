#pragma once

#include "../../graphics/IDisplayModule.hpp"

class Food {
    public:
        Food() = default;
        ~Food()= default;
        std::pair<int, int> getFoodPos();
        void spawnFood();
        void displayFood(IDisplayModule &dsp);
    private:
        std::pair<int, int> _food;
        Rectangle _recFood;
};

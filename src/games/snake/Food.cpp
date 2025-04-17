#include "Food.hpp"

std::pair<int, int> Food::getFoodPos()
{
   return _food; 
}

void Food::spawnFood()
{
    _food = {std::rand() % 50 + 25, std::rand() % 25 + 12};
}

void Food::displayFood(IDisplayModule &dsp)
{
    _recFood.fillRect(true);
    _recFood.setColor(Color::ColorID::RED);
    _recFood.getTransform().getPosition().setPosition(
            _food.first, _food.second);
    _recFood.getTransform().getSize().setPosition(1, 1);
    dsp.draw(_recFood);
}

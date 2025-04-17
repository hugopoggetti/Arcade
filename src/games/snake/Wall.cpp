#include "Wall.hpp"
#include <cstddef>

void Wall::displayWall(IDisplayModule &dsp, std::size_t x, std::size_t y)
{
    _wall.fillRect(false);
    _wall.setColor(Color::ColorID::GREEN);
    _wall.getTransform().getPosition().setPosition(
            (double)x, (double)y);
    _wall.getTransform().getSize().setPosition(50, 25);
    dsp.draw(_wall);
}

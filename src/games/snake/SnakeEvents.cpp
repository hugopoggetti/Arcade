#include "SnakeEvents.hpp"
#include "Snake.hpp"
#include <cmath>
#include <cstdlib>
#include <endian.h>

SnakeEvents::SnakeEvents() : _d(S_RIGHT) {}

SnakeEvents::~SnakeEvents() {}

void SnakeEvents::onKeyPressed(IGameModule *game, KeyPressedEvent *event)
{
    int key = event->getKey();
    auto snake = dynamic_cast<Snake *>(game);

    switch (key) {
        case ArcadeKey::UP:
            if (_d != S_DOWN)
                _d = S_UP;
            break;
        case ArcadeKey::DOWN:
            if (_d != S_UP)
                _d = S_DOWN;
            break;
        case ArcadeKey::LEFT:
            if (_d != S_RIGHT)
                _d = S_LEFT;
            break;
        case ArcadeKey::RIGHT:
            if (_d != S_LEFT)
                _d = S_RIGHT;
            break;
        case ArcadeKey::SPACE:
            snake->speedUp();
            break;
        case ArcadeKey::Q:
            snake->reset(true);
            break;
    }
}

Direction SnakeEvents::getDirection()
{
    return _d;
}

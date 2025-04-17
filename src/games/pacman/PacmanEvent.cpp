#include "PacmanEvent.hpp"
#include "Pacman.hpp"
#include <cmath>
#include <cstdlib>
#include <endian.h>

void PacmanEvents::onKeyPressed(IGameModule *game, KeyPressedEvent *event)
{
    int key = event->getKey();
    auto pacman = dynamic_cast<Pacman *>(game);

    switch (key) {
        case ArcadeKey::UP:
            pacman->moveUp();
            break;
        case ArcadeKey::DOWN:
            pacman->moveDown();
            break;
        case ArcadeKey::LEFT:
            pacman->moveLeft();
            break;
        case ArcadeKey::RIGHT:
            pacman->moveRight();
            break;
        case ArcadeKey::RETURN:
            break;
    }
}

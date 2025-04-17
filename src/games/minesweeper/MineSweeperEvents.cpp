#include "MineSweeperEvents.hpp"
#include "Minesweeper.hpp"

void MineSweeperEvents::onKeyPressed(IGameModule *game, KeyPressedEvent *event)
{
    int key = event->getKey();
    auto sweeper = dynamic_cast<MineSweeper *>(game);

    if (key == ArcadeKey::SPACE)
        sweeper->reset(0);
}

void MineSweeperEvents::onMouseButtonPressed
    (IGameModule *game, MouseButtonPressedEvent *event)
{
    auto sweeper = dynamic_cast<MineSweeper *>(game);

    auto bouton = event->getButton();

    if (bouton == ArcadeMouseButton::MOUSE2) {
        sweeper->markCell(event->getPosition());
    }
    if (bouton == ArcadeMouseButton::MOUSE1) {
        sweeper->openCell(event->getPosition());
    }
}

void MineSweeperEvents::onMouseMove(IGameModule *game, MouseMoveEvent *event)
{ 
    (void)game;
    _mousePos = event->getPosition();
}


Position MineSweeperEvents::getMousePos()
{
    return _mousePos;
}

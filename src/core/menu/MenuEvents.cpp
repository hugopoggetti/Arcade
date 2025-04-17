#include "MenuEvents.hpp"
#include <cmath>
#include <cstdlib>
#include "Menu.hpp"

MenuEvents::MenuEvents() {}

MenuEvents::~MenuEvents() {}

void MenuEvents::onKeyPressed(IGameModule *game, KeyPressedEvent *event)
{
    int key = event->getKey();

    auto menu = dynamic_cast<Menu *>(game);

    switch (key) {
        case ArcadeKey::P:
            return menu->nextGraphic();
        case ArcadeKey::O:
            return menu->nextGraphic();
        case ArcadeKey::UP:
            return menu->selctGraphic(1);
        case ArcadeKey::DOWN:
            return menu->selctGraphic(0);
        case ArcadeKey::LEFT:
            return menu->selectGame(1);
        case ArcadeKey::RIGHT:
            return menu->selectGame(0);
        case ArcadeKey::RETURN:
            return menu->starGame();
        case ArcadeKey::M:
            return menu->backToMenu();
        case ArcadeKey::ESCAPE:
            return menu->stop();
        case ArcadeKey::BACKSPACE:
            return menu->nextGame();
    }
}

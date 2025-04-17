#include "NcurseLib.hpp"
#include <iomanip>
#include <ncurses.h>
#include <queue>
#include <iostream>

void NcurseLib::KeyBoardEvents(const int ch, std::queue<IEvent *> &events) const
{
    if (ch != ERR) {
        switch (ch) {
            case KEY_UP:
                events.push(new KeyPressedEvent(ArcadeKey::UP));
                break;
            case KEY_DOWN:
                events.push(new KeyPressedEvent(ArcadeKey::DOWN));
                break;
            case KEY_LEFT:
                events.push(new KeyPressedEvent(ArcadeKey::LEFT));
                break;
            case KEY_RIGHT:
                events.push(new KeyPressedEvent(ArcadeKey::RIGHT));
                break;
            case 27:
                events.push(new KeyPressedEvent(ArcadeKey::ESCAPE));
                break;
            case 'o':
                events.push(new KeyPressedEvent(ArcadeKey::O));
                break;
            case 'p':
                events.push(new KeyPressedEvent(ArcadeKey::P));
                break;
            case '\n':
                events.push(new KeyPressedEvent(ArcadeKey::RETURN));
                break;
            case 'm':
                events.push(new KeyPressedEvent(ArcadeKey::M));
                break;
            case ' ':
                events.push(new KeyPressedEvent(ArcadeKey::SPACE));
                break;
            case 'r':
                events.push(new KeyPressedEvent(ArcadeKey::R));
                break;
            case 'd':
                events.push(new KeyPressedEvent(ArcadeKey::D));
                break;
            case 'q':
                events.push(new KeyPressedEvent(ArcadeKey::Q));
                break;
            case 's':
                events.push(new KeyPressedEvent(ArcadeKey::S));
                break;
            case 'z':
                events.push(new KeyPressedEvent(ArcadeKey::Z));
                break;
            case KEY_F(1):
                events.push(new KeyPressedEvent(ArcadeKey::F1));
                break;
            case KEY_F(2):
                events.push(new KeyPressedEvent(ArcadeKey::F2));
                break;
            case KEY_BACKSPACE:
                events.push(new KeyPressedEvent(ArcadeKey::BACKSPACE));
                break;
            default:
                events.push(new KeyPressedEvent(static_cast<ArcadeKey>(ch)));
                break;
        }
    }
}

void NcurseLib::MouseEvents(const int ch, std::queue<IEvent *> &events) const
{
    if (ch == KEY_MOUSE) {
        MEVENT event;
        if (getmouse(&event) == OK) {
            Position pos(event.x * (double)_grid.first / (double)terminalWidth,
                event.y * (double)_grid.second / (double)terminalHeight);

            if (event.bstate & BUTTON1_PRESSED) {
                events.push(new MouseButtonPressedEvent
                        (ArcadeMouseButton::MOUSE1, pos.getX() , pos.getY()));
            } 
            if (event.bstate & BUTTON1_RELEASED) {
                events.push(new MouseButtonReleasedEvent
                        (ArcadeMouseButton::MOUSE1, pos.getX(), pos.getY()));
            } 
            if (event.bstate & BUTTON3_PRESSED) {
                events.push(new MouseButtonPressedEvent
                        (ArcadeMouseButton::MOUSE2, pos.getX(), pos.getY()));
            } 
            if (event.bstate & BUTTON3_RELEASED) {
                events.push(new MouseButtonReleasedEvent
                        (ArcadeMouseButton::MOUSE2, pos.getX(), pos.getY()));
            }
            if (event.bstate & REPORT_MOUSE_POSITION) {
                events.push(new MouseMoveEvent(pos));
            }
        }
    }
}

#ifndef __LISTENER__
    #define __LISTENER__

#include "Events.hpp"

#include "../games/IGameModule.hpp"

class KeyPressedEvent;
class KeyReleasedEvent;
class MouseButtonPressedEvent;
class MouseButtonReleasedEvent;
class MouseMoveEvent;
class WindowClosedEvent;
class WindowMoveEvent;
class WindowResizeEvent;

class Listener {
    public:
        virtual void onKeyPressed(IGameModule *, KeyPressedEvent *) {}
        virtual void onKeyReleased(IGameModule *, KeyReleasedEvent *) {}
        virtual void onMouseButtonPressed(IGameModule *, MouseButtonPressedEvent *) {};
        virtual void onMouseButtonReleased(IGameModule *, MouseButtonReleasedEvent *) {};
        virtual void onMouseMove(IGameModule *, MouseMoveEvent *) {};
        virtual void onWindowClosed(IGameModule *, WindowClosedEvent *) {};
        virtual void onWindowMove(IGameModule *, WindowMoveEvent *) {};
        virtual void onWindowResize(IGameModule *, WindowResizeEvent *) {};
};

#endif

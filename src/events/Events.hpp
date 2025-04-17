#ifndef __EVENTS__
    #define __EVENTS__

#include "EventsSystem.hpp"
#include "Listener.hpp"

#include "../games/IGameModule.hpp"
#include "../graphics/transform/Position.hpp"

class IEvent {
    public:
        IEvent() = default;
        virtual ~IEvent() = default;
        virtual void dispatch(IGameModule *game, Listener *listener) = 0;
};

class KeyPressedEvent : public IEvent {
    public:
        KeyPressedEvent(ArcadeKey key) : _key(key) {}
        ~KeyPressedEvent() = default;
        int getKey() const { return this->_key; }
        virtual void dispatch(IGameModule *game, Listener *listener) { listener->onKeyPressed(game, this); }
    private:
         ArcadeKey _key;
};

class KeyReleasedEvent : public KeyPressedEvent {
    public:
        KeyReleasedEvent(ArcadeKey key) : KeyPressedEvent(key) {}
        ~KeyReleasedEvent() = default;
        virtual void dispatch(IGameModule *game, Listener *listener) { listener->onKeyReleased(game, this); }
};

class MouseButtonPressedEvent : public IEvent {
public:
    MouseButtonPressedEvent(ArcadeMouseButton btn, double x, double y) : _btn(btn), _pos(x, y) {};
    ArcadeMouseButton getButton() const { return this->_btn; }
    const Position &getPosition() const { return this->_pos; }
    virtual void dispatch(IGameModule *game, Listener *listener) {
        listener->onMouseButtonPressed(game, this);
    }
private:
    ArcadeMouseButton _btn;
    Position _pos;
};

class MouseButtonReleasedEvent : public MouseButtonPressedEvent {
public:
    MouseButtonReleasedEvent(ArcadeMouseButton btn, double x, double y) : MouseButtonPressedEvent(btn, x, y) {};
    virtual void dispatch(IGameModule *game, Listener *listener) {
        listener->onMouseButtonReleased(game, this);
    }
};

class MouseMoveEvent : public IEvent {
public:
    MouseMoveEvent(const Position &pos) : _pos(pos) {};
    
    const Position &getPosition() const {
        return this->_pos;
    }
    
    virtual void dispatch(IGameModule *game, Listener *listener) {
        listener->onMouseMove(game, this);
    }
private:
    Position _pos;
};

class WindowClosedEvent : public IEvent {
        WindowClosedEvent() = default;
        ~WindowClosedEvent() = default;
        virtual void dispatch(IGameModule *game, Listener *listener) { listener->onWindowClosed(game, this); }
};

class WindowMoveEvent : public IEvent {
    public:
        WindowMoveEvent(const Position &pos) : _pos(pos) {}
        ~WindowMoveEvent() = default;
        const Position &getPosition() const { return _pos; }
        virtual void dispatch(IGameModule *game, Listener *listener) { listener->onWindowMove(game, this); }
    private:
        Position _pos;
};

class WindowResizeEvent : public IEvent {
    public:
        WindowResizeEvent(const Size &size) : _size(size) {}
        ~WindowResizeEvent() = default;
        const Size &getSize() const { return _size; }
        virtual void dispatch(IGameModule *game, Listener *listener) { listener->onWindowResize(game, this); }
    private:
        Size _size;
};

#endif

#include "EventManager.hpp"
#include <iostream>

void EventManager::pollEvents(IDisplayModule *display)
{
    _events = display->pollEvents();
}

void EventManager::clear()
{
    this->_listeners.clear();
    this->_listenersGui.clear();
}

void EventManager::registerGameListeners(IGameModule *game)
{
    _listeners = game->getGameListeners();
}

void EventManager::registerGuiListeners(IGameModule *gui)
{
    _listenersGui = gui->getGameListeners();
}

void EventManager::registerListener(Listener *listener)
{
    _listeners.push_back(listener);
}

void EventManager::unregisterListener(Listener *listener)
{
    for (auto it = _listeners.begin(); it != _listeners.end(); ++it) {
        if ((*it) == listener) {
            _listeners.erase(it);
            return;
        }
    }
}

void EventManager::transmitEvents(IGameModule *gui, IGameModule *game)
{
    std::size_t sizeStack = _events.size();
    std::queue<IEvent *> events = _events;

    if (game != nullptr) {
        for (auto it = _listeners.begin(); it != _listeners.end(); ++it) {
            for (std::size_t i = 0; i < sizeStack; i++) {
                events.front()->dispatch(game, (*it));
                events.push(events.front());
                events.pop();
            }
        }
    }
    for (auto it = _listenersGui.begin(); it != _listenersGui.end(); ++it) {
        for (std::size_t i = 0; i < sizeStack; i++) {
            _events.front()->dispatch(gui, (*it));
            _events.push(_events.front());
            _events.pop();
        }
    }
}

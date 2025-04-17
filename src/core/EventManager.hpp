#ifndef __EVENT_MANAGER__
    #define __EVENT_MANAGER__

#include <queue>
#include <vector>

#include "../events/Events.hpp"
#include "../events/Listener.hpp"

class EventManager {
    public:
        EventManager() = default;
        void pollEvents(IDisplayModule *display);
        void clear();
        void registerGameListeners(IGameModule *game);
        void registerGuiListeners(IGameModule *gui);
        void registerListener(Listener *listener);
        void unregisterListener(Listener *listener);
        void transmitEvents(IGameModule *gui, IGameModule *game);
    private:
        std::queue<IEvent *> _events;
        std::vector<Listener *> _listeners;
        std::vector<Listener *> _listenersGui;
};

#endif

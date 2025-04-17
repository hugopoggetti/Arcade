#pragma once

#include "../EventManager.hpp"

class MenuEvents : public Listener {
    public:
        MenuEvents();
        ~MenuEvents();
        void onKeyPressed(IGameModule *game, KeyPressedEvent *event) override;
    private:
};

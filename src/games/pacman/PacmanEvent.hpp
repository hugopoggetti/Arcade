#pragma once

#include "../../core/EventManager.hpp"

class PacmanEvents : public Listener {
    public:
        PacmanEvents() = default;
        ~PacmanEvents() = default;
        void onKeyPressed(IGameModule *game, KeyPressedEvent *event) override;
    private:
};

#pragma once

#include "../../core/EventManager.hpp"

enum Direction {UKN, S_UP, S_DOWN, S_LEFT, S_RIGHT};

class SnakeEvents : public Listener {
    public:
        SnakeEvents();
        ~SnakeEvents();
        void onKeyPressed(IGameModule *game, KeyPressedEvent *event) override;
        Direction getDirection();
    private:
        Direction _d;
};

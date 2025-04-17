#pragma once

#include "../../core/EventManager.hpp"


class MineSweeperEvents : public Listener {
    public:
        MineSweeperEvents() = default;
        ~MineSweeperEvents() = default;
        void onKeyPressed(IGameModule *game, KeyPressedEvent *event) override;
        void onMouseButtonPressed
            (IGameModule *game, MouseButtonPressedEvent *event) override;
        void onMouseMove(IGameModule *game, MouseMoveEvent *event) override;
        Position getMousePos();
    private:
        Position _mousePos;
};

#pragma once

#include <cstddef>
#include "../../graphics/IDisplayModule.hpp"

class Wall {
    public:
        Wall() = default;
        ~Wall() = default;
        void displayWall(IDisplayModule &dsp, std::size_t X, std::size_t Y);
    private:
        Rectangle _wall;
};

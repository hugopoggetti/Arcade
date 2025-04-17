#pragma once

#include <vector>
#include "../../graphics/IDisplayModule.hpp"

enum Element { _P, _M, _V, _W, _I, _G };

class Map {
public:
    Map() = default;
    ~Map() = default;

    void displayMap(int startx, int starty,
        const std::vector<std::vector<Element>>& map,
        IDisplayModule* dsp);

    std::vector<std::vector<Element>> getMap() const;

private:
    const std::vector<std::vector<Element>> _map = {
        { _M, _M, _M, _M, _M, _M, _M, _M, _M, _M, _M, _M, _M, _M, _M, _M, _M, _M, _M},
        { _M, _I, _P, _P, _P, _P, _P, _P, _P, _M, _P, _P, _P, _P, _P, _P, _P, _I, _M},
        { _M, _W, _M, _M, _P, _M, _M, _M, _P, _M, _P, _M, _M, _M, _P, _M, _M, _W, _M},
        { _M, _P, _P, _P, _P, _P, _P, _P, _P, _P, _P, _P, _P, _P, _P, _P, _P, _P, _M},
        { _M, _P, _M, _M, _P, _M, _P, _M, _M, _M, _M, _M, _P, _M, _P, _M, _M, _P, _M},
        { _M, _P, _P, _P, _P, _M, _P, _P, _P, _M, _P, _P, _P, _M, _P, _P, _P, _P, _M},
        { _M, _M, _M, _M, _P, _M, _M, _M, _P, _M, _P, _M, _M, _M, _P, _M, _M, _M, _M},
        { _V, _V, _V, _M, _P, _M, _P, _P, _P, _P, _P, _P, _P, _M, _P, _M, _V, _V, _V},
        { _M, _M, _M, _M, _P, _M, _P, _M, _M, _P, _M, _M, _P, _M, _P, _M, _M, _M, _M},
        { _P, _P, _P, _P, _P, _P, _P, _M, _P, _G, _P, _M, _P, _P, _P, _P, _P, _P, _P},
        { _M, _M, _M, _M, _P, _M, _P, _M, _M, _M, _M, _M, _P, _M, _P, _M, _M, _M, _M},
        { _V, _V, _V, _M, _P, _M, _P, _P, _P, _P, _P, _P, _P, _M, _P, _M, _V, _V, _V},
        { _M, _M, _M, _M, _P, _M, _P, _M, _M, _M, _M, _M, _P, _M, _P, _M, _M, _M, _M},
        { _M, _P, _P, _P, _P, _P, _P, _P, _P, _M, _P, _P, _P, _P, _P, _P, _P, _P, _M},
        { _M, _P, _M, _M, _P, _M, _M, _M, _P, _M, _P, _M, _M, _M, _P, _M, _M, _P, _M},
        { _M, _W, _P, _M, _P, _P, _P, _P, _P, _P, _P, _P, _P, _P, _P, _M, _P, _W, _M},
        { _M, _M, _P, _M, _P, _M, _P, _M, _M, _M, _M, _M, _P, _M, _P, _M, _P, _M, _M},
        { _M, _P, _P, _P, _P, _M, _P, _P, _P, _M, _P, _P, _P, _M, _P, _P, _P, _P, _M},
        { _M, _P, _M, _M, _M, _M, _M, _M, _P, _M, _P, _M, _M, _M, _M, _M, _M, _P, _M},
        { _M, _I, _P, _P, _P, _P, _P, _P, _P, _P, _P, _P, _P, _P, _P, _P, _P, _I, _M},
        { _M, _M, _M, _M, _M, _M, _M, _M, _M, _M, _M, _M, _M, _M, _M, _M, _M, _M, _M},
    };
};

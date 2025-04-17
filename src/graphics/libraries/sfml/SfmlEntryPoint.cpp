#include "SfmlLib.hpp"

extern "C" IDisplayModule *getGraphics()
{
    return new SfmlLib;
}

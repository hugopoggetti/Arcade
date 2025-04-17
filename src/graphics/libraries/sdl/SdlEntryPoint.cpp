#include "SdlLib.hpp"

extern "C" IDisplayModule *getGraphics()
{
    return new SdlLib;
}

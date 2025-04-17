#include "NcurseLib.hpp"

extern "C" IDisplayModule *getGraphics()
{
	return  new NcurseLib;
}

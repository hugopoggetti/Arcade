#include "Snake.hpp"

extern "C" IGameModule *getGame()
{
	return new Snake;
}

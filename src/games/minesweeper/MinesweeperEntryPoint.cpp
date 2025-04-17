#include "Minesweeper.hpp"

extern "C" IGameModule *getGame()
{
	return new MineSweeper;
}

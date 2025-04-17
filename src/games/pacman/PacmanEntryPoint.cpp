#include "Pacman.hpp"
#include <tuple>

IGameModule *game = nullptr;

__attribute__((constructor))
void ctor()
{
    game = new Pacman;
}

__attribute__((destructor))
void dtor()
{
	delete game;
}

extern "C" IGameModule *getGame()
{
	return game;
}

#include "Game.h"

int main()
{
	auto result = TheGame::instance()->init(
		"Chapter 1",
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		640,
		580
	);

	if (result)
		TheGame::instance()->runloop();

	TheGame::instance()->clean();
	return 0;
}
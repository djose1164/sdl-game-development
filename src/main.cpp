#include "Game.h"

int main()
{
	Game game;
	auto result = game.init(
		"Chapter 1",
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		640,
		580
	);

	if (result)
		game.runloop();

	game.clean();
	return 0;
}
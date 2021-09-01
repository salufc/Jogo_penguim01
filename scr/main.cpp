#include <iostream>
#include "game.hpp"

int main(int argc, char** argv)
{

	Game::getInstance();
	Game::getInstance().set_game(1024,600,"JOGO");
	Game::getInstance().init_game();
	Game::getInstance().Run();


	return 0;
}
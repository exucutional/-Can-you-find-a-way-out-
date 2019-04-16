#ifndef GAME_HPP_
#define GAME_HPP_
#include "gameobjects.hpp"
class AssetManager
{
	;
};
class App
{
	sf::RenderWindow window;
	Player player;
	AssetManager aManager;
public:
	Game() {}
	void run();
	int8_t run();
	int8_t gameLoop();
};

#endif //GAME_HPP_
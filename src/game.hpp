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
<<<<<<< HEAD
	Game() {}
	void run();
=======
	int8_t run();
	int8_t gameLoop();
>>>>>>> 2627b3ede6c71f435e838b902612e8d613497dd2
};

#endif //GAME_HPP_
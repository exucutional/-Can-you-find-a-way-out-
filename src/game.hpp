#ifndef GAME_HPP_
#define GAME_HPP_
#include "gameobjects.hpp"

class Game
{
	sf::RenderWindow window;
	Player player;
public:
	void run();
};

#endif //GAME_HPP_
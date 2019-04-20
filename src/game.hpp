#ifndef GAME_HPP_
#define GAME_HPP_
#include "gameobjects.hpp"
class ObjectManager
{
	std::vector<Gameobject*> objVec;
public:
	ObjectManager();
	ObjectManager(unsigned objVecInit) : objVec(objVecInit) {}
	~ObjectManager();
};
class App
{
	sf::RenderWindow window;
	Player player;
	ObjectManager oManager;
public:
	App() {}
	int run();
	int gameLoop();
};
#endif //GAME_HPP_
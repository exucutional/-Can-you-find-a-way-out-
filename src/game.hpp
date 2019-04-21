#ifndef GAME_HPP_
#define GAME_HPP_
#include "gameobjects.hpp"
extern const sf::Time deltaTime;
class ObjectManager
{
	std::vector<GameObject*> objVec;
public:
	ObjectManager() {}
	void addObject(GameObject* newObj);
	const GameObject* getObject(std::size_t num) const;
	const std::size_t getSize() const;
	void render(sf::RenderTarget& target, sf::Time frameTime);
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
	int init();
	void gameStep();
	void render(sf::RenderTarget& target, sf::Time frameTime);
	int gameLoop();
};
#endif //GAME_HPP_
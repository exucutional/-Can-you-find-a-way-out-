#include "game.hpp"

const sf::Time deltaTime = sf::seconds(0.01f);

void map_test()
{
	ObjectManager oManager;
	Map map(oManager);
	map.generate(200, 0.4, 4, 3, 4);
}
int main()
{
	//map_test();
	App game;
	int exitCode = game.run();
	return exitCode;
	return 0;
}
#include "game.hpp"

const sf::Time deltaTime = sf::seconds(0.01f);

//virtual Collide(obj[i], obj[j]);

int LuaTest()
{
	LuaScript script("src/script.lua");
	std::string filename = script.get<std::string>("testString");
	int posX = script.get<int>("player.pos.lol.Z");
	std::cout << "filename: " << filename << "\npos:" << posX << std::endl; 
	script.testprint("Hello world!\n");
	return EXIT_SUCCESS;
}
int main()
{
    App game;
    int exitCode = game.run();
    return exitCode;
    return 0;
}
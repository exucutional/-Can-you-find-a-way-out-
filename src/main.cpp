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
void LuaBridgeTest()
{
	lua_State* L = luaL_newstate();
    luaL_dofile(L, "src/script.lua");
    luaL_openlibs(L);
    lua_pcall(L, 0, 0, 0);
    luabridge::LuaRef s = luabridge::getGlobal(L, "testString");
    luabridge::LuaRef n = luabridge::getGlobal(L, "number");
    std::string luaString = s.cast<std::string>();
    int answer = n.cast<int>();
	std::cout << luaString << std::endl;
    std::cout << "And here's our number:" << answer << std::endl;
}
int main()
{
	LuaBridgeTest();
    App game;
    int exitCode = game.run();
    return exitCode;
    return 0;
}
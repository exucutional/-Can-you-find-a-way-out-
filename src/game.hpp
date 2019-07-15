#ifndef GAME_HPP_
#define GAME_HPP_
#include <iostream>
#include <cassert>
#include <memory>
#include <vector>
#include <SFML/Graphics.hpp>
#include "assert.hpp"
#include "luaScript.hpp"
#include "state.hpp"
#include "statemanager.hpp"
#include "collision.hpp"
#include "LuaBridge.h"
#include "sol/sol.hpp"
#ifndef NDEBUG
#define __DEBUG_EXEC(code) code
#else
#define __DEBUG_EXEC(code) ;
#endif

extern const sf::Time deltaTime;

class App
{
	sf::RenderWindow window;
	AssetManager asManager;
	StateManager sManager;
public:
	App();
	~App();
	int run();
};
#endif //GAME_HPP_
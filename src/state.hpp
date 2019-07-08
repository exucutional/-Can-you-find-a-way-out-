#ifndef STATE_HPP_
#define STATE_HPP_

#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <memory>
#include "gameobjects.hpp"
#include "objectmanager.hpp"
#include "assetmanager.hpp"

extern const sf::Time deltaTime;

#ifndef NDEBUG
#define __DEBUG_EXEC(code) code
#else
#define __DEBUG_EXEC(code) ;
#endif

enum STATE
{
	CLOSED_STATE = -1,
	MENU_STATE = 0,
	GAME_STATE = 1,
};
class State
{
protected:
	ObjectManager oManager;
	sf::RenderWindow& window;
	AssetManager& asManager;
	int nextStateIndex;
	bool isPaused;
public:
	State(sf::RenderWindow& window_, AssetManager& asManager_):
	window(window_),
	asManager(asManager_) 
	{}
	virtual ~State() {}
	virtual void init() = 0;
	virtual void pause() = 0;
	virtual void resume() = 0;
	virtual void processInput() = 0;
	virtual void update() = 0;
	virtual int gameLoop() = 0;
	virtual void render(sf::RenderTarget& target, sf::Time frameTime) = 0;
};
class MenuState : public State
{
public:
	MenuState(sf::RenderWindow& window_, AssetManager& asManager_);
	~MenuState();
	void init();
	void pause();
	void resume();
	void processInput();
	void update();
	int gameLoop();
	void render(sf::RenderTarget& target, sf::Time frameTime);
};
class GameState : public State
{
	Player player;
public:
	GameState(sf::RenderWindow& window_, AssetManager& asManager_);
	~GameState();
	void init();
	void pause();
	void resume();
	void processInput();
	void update();
	int gameLoop();
	void render(sf::RenderTarget& target, sf::Time frameTime);
};
#endif //STATE_HPP_
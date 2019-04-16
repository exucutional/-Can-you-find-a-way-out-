#include "gameobjects.hpp"

void PlayerController::interaction()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
		interrupt.exitSet(true);
}

void Gameobjects::physHandler()
{
	position.x += vec.x;
	position.y += vec.y;
	if (vec.x)
		vec .x -= (vec.x > 0) ? 1 : -1;
	if (vec.y)
		vec.y -= (vec. y > 0) ? 1 : -1;
}
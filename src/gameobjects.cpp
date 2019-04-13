#include "gameobjects.hpp"

void PlayerController::interaction()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
		interrupt.exitSet(true);
}
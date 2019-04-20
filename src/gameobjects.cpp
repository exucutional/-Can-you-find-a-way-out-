#include "gameobjects.hpp"
void Gameobject::physHandler()
{
	position.x += velocity.x;
	position.y += velocity.y;
	if (velocity.x)
		veloctiy.x -= (velocity.x > 0) ? 1 : -1;
	if (velocity.y)
		velocity.y -= (velocity.y > 0) ? 1 : -1;
}
void Gameobject::render(sf::RenderWindow& window)
{
	sprite.setPosition(position);
	window.clear(sf::Color(200, 100, 50));
	window.draw(sprite);
}


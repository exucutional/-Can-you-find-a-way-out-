#include <cassert>
#include "game.hpp"

void Game::run()
{
	window.create(sf::VideoMode(1500, 1000), "SFML works!");
    window.setMouseCursorVisible(true);
    sf::Texture texture;
    if (!texture.loadFromFile("texture/ball.png"))
		assert(0);
	texture.setSmooth(true);
	sf::Sprite sprite;
	sprite.setTexture(texture);
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        player.control.interaction();
        if (player.control.interrupt.exit())
        	break;
        window.clear();
        window.draw(sprite);
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
        	sprite.move(sf::Vector2f(0.f, -1.f));
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
        	sprite.move(sf::Vector2f(1.f, 0.f));
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
        	sprite.move(sf::Vector2f(0.f, 1.f));
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
        	sprite.move(sf::Vector2f(-1.f, 0.f));
        window.display();
    }
}
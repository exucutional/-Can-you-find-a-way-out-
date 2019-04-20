#include <cassert>
#include "game.hpp"

int App::run()
{
	window.create(sf::VideoMode(1500, 1000), "SFML works!");
    window.setMouseCursorVisible(true);
    sf::Texture texture;
    if (!texture.loadFromFile("texture/ball.png"))
		assert(0);
	texture.setSmooth(true);
	sf::Sprite sprite;
	sprite.setTexture(texture);
    GameObject obj({0, 0}, {0, 0}, sprite);
    player.mainperson = obj;
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        player.interaction();
        if (player.control.interrupt.exit())
        	break;
        obj.physHandler();
        obj.render();
        window.display();
    }
    return EXIT_SUCCESS;
}
int App::gameLoop()
{
    return EXIT_SUCCESS;
}
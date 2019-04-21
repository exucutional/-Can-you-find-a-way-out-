#include <iostream>
#include <cassert>
#include <SFML/Graphics.hpp>
#include "game.hpp"

const sf::Time deltaTime = sf::seconds(0.01f);

//CollisionDetect
//CollisionResponse
//AccessAlidBoundyBox AABB
//OOBB ObjectOrientedBoundyBox OOBB

//virtual Collide(obj[i], obj[j]);
int main()
{
    App game;
    int exitCode = game.run();
    return exitCode;
}
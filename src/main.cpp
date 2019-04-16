#include <iostream>
#include <cassert>
#include <SFML/Graphics.hpp>
#include "game.hpp"


//CollisionDetect
//CollisionResponse
//AccessAlidBoundyBox AABB
//OOBB ObjectOrientedBoundyBox OOBB

//virtual Collide(obj[i], obj[j]);
int main()
{
    App game;
    int8_t exitCode = game.run();
    return exitCode;
}
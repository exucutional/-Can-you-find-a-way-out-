#ifndef COLLISION_HPP_
#define COLLISION_HPP_
#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <cmath>
#include <cassert>
#include <sstream>
#include "luaScript.hpp"
#ifndef NDEBUG
#define __DEBUG_EXEC(code) code
#else
#define __DEBUG_EXEC(code) ;
#endif
class Collider
{
	sf::CircleShape circle;
	sf::RectangleShape rectangle;
	sf::ConvexShape convex;
	sf::Text info;
	sf::Font font;
public:
	Collider();
	const sf::RectangleShape& getOBB();
	void setOBBposition(float x, float y);
	void setOBBposition (const sf::Vector2f& position);
	void setOBBsize(const sf::Vector2f &size);
	const sf::Text& getInfo();
	~Collider();
};
class Collision
{
public:
	Collider collider;
	Collision();
	~Collision();
	bool intersect(const sf::CircleShape& circle1, const sf::CircleShape& circle2, sf::Vector2f* mtv_ptr = nullptr);
	bool intersect(const sf::RectangleShape& rectangle1, const sf::RectangleShape& rectangle2, sf::Vector2f* mtv_ptr = nullptr);
	bool intersect(const sf::ConvexShape& convex1, const sf::ConvexShape& convex2, sf::Vector2f* mtv_ptr = nullptr);
	bool SATcollison(const sf::ConvexShape& convex1, const sf::ConvexShape& convex2);
};
#endif //COLLISION_HPP_
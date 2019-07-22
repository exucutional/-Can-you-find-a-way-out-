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
enum COLLIDE_MODE 
{
	CIRCLE_MODE = 0,
	RECT_MODE, 
	CONVEX_MODE,
};
class Collider
{
	sf::CircleShape circle;
	sf::RectangleShape rectangle;
	sf::ConvexShape convex;
	sf::Text info;
	sf::Font font;
public:
	Collider();
	const sf::CircleShape& getCircle() const;
	const sf::RectangleShape& getRect() const;
	const sf::ConvexShape& getConvex() const;
	void setRectPosition(float x, float y);
	void setRectPosition (const sf::Vector2f& position);
	void setRectSize(const sf::Vector2f &size);
	void setConvexPointCount(std::size_t count);
	void setConvexPoint(std::size_t index, const sf::Vector2f& point);
	const sf::Text& getInfo() const;
	~Collider();
};
class Collision
{
public:
	Collision();
	~Collision();
	bool intersect(const sf::CircleShape& circle1, const sf::CircleShape& circle2, sf::Vector2f* mtv_ptr = nullptr);
	bool intersect(const sf::RectangleShape& rectangle1, const sf::RectangleShape& rectangle2, sf::Vector2f* mtv_ptr = nullptr);
	bool intersect(const sf::ConvexShape& convex1, const sf::ConvexShape& convex2, sf::Vector2f* mtv_ptr = nullptr);
	bool isCollide(const Collider& collider1, const Collider& collider2, int collideMode, sf::Vector2f* mtv_ptr = nullptr);
};
#endif //COLLISION_HPP_
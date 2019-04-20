#ifndef GAMEOBJECT_HPP_
#define GAMEOBJECT_HPP_

#include <SFML/Graphics.hpp>
#include "animation.hpp"
template <typename T>
struct Vector
{
	T x, y;
	Vector() : x (0), y (0) {}
	template <typename U1, typename U2>
	Vector (U1 x, U2 y) : x ((T) x), y ((T) y) {}
	template <typename U>
	Vector (const Vector <U>& vec) : x ((T) vec.x), y ((T) vec.y) {}
	template <typename U>
	Vector (const sf::Vector2 <U>& vec) : x ((T) vec.x), y ((T) vec.y) {}
};
using Vec = Vector <float>;
class ControlManager
{
};
class GameObject
{
	Vec position;
	AnimationManager aManager;
public:
	GameObject(Vec pos) : position(pos), size(sz), aManager() {}
	void render(sf::RenderWindow& window);
	~GameObject();
};
class StaticGameObject : public GameObject
{
};
class DynamicGameObject : public GameObject
{
	Vec velocity;
	ControlManager cManager;
public:
	void physHandler();
	void control();
};
class Player
{
	GameObject* mgObj;
public:
	Player();
	void control();
};

#endif //GAMEOBJECT_HPP_
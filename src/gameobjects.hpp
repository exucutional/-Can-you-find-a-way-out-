#ifndef GAMEOBJECT_HPP_
#define GAMEOBJECT_HPP_

#include <SFML/Graphics.hpp>

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
class Gameobject
{
	Vec position;
	Vec size;
	sf::Sprite sprite;
public:
	Gameobject(Vec pos, Vec sz, sf::Sprite spr) : position(pos), size(sz), sprite(spr) {}
	~Gameobject();
};
class Stats
{
	int hp;
	int mp;
public:
	Stats() : hp(0), mp(0) {}
};
class Character : public Gameobject
{
	Stats stats;
	//class CharacterController control;	
	//class CharacterAnimationController animcontrol;
	//class CharacterCollisionHandler collcontrol;
public:
	Character();
	~Character();
};
class CharacterController
{
	;
};
class CharacterAnimationController
{
	;
};
class CharacterCollisionHandler 
{
	;
};
class InterruptHandler
{
	bool MenuCall;
	bool ExitCall;
public: 
	InterruptHandler() : MenuCall(false), ExitCall(false) {}
	void exitSet(bool val) {ExitCall = val;}
	bool exit() {return ExitCall;}
};
class PlayerController
{
public:
	InterruptHandler interrupt;
	void interaction();
};
class Player
{
	//Character character;
public:
	PlayerController control;
};

#endif //GAMEOBJECT_HPP_
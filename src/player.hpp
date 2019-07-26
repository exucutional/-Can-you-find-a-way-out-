#ifndef PLAYER_HPP_
#define PLAYER_HPP_
#include <cmath>
#include "objectmanager.hpp"
#include "vector_func.hpp"
class Player
{
	std::shared_ptr<DynamicGameObject> obj_ptr;
	ObjectManager& oManager;
	sf::Time shootfreq;
	sf::Clock clock;
public:
	Player(ObjectManager& oManager);
	~Player();
	void setObject(DynamicGameObject* obj_ptr);
	void setObject(std::shared_ptr<DynamicGameObject> obj_ptr);
	sf::Vector2f getPosition() const;
	std::shared_ptr<DynamicGameObject> getObject();
	void control();
	void shoot(sf::RenderWindow& window);
};
#endif //PLAYER_HPP_
#include "player.hpp"
static const float SPEED_RATE = 200;
static const double PI = 3.1415926535;
Player::Player(ObjectManager& oManager_):
oManager(oManager_),
shootfreq(sf::milliseconds(250))
{
	__DEBUG_EXEC(std::cout << "Player()\n");
}
Player::~Player()
{
	__DEBUG_EXEC(std::cout << "~Player()\n");
}
void Player::setObject(DynamicGameObject* obj_ptr_)
{
	assert(obj_ptr_);
	obj_ptr = std::shared_ptr<DynamicGameObject>(obj_ptr_);
}
void Player::setObject(std::shared_ptr<DynamicGameObject> obj_ptr_)
{
	assert(obj_ptr_);
	obj_ptr = obj_ptr_;
}
void Player::control()
{
	assert(obj_ptr);
	std::size_t aNum = obj_ptr->getCurrentAnimationNum();
	sf::Vector2f velocity = obj_ptr->getVelocity();
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
		aNum = aDown;
		velocity.y = SPEED_RATE;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
		aNum = aUp;
		velocity.y = -SPEED_RATE;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
		aNum = aLeft;
		velocity.x = -SPEED_RATE;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
		aNum = aRight;
		velocity.x = SPEED_RATE;
	}
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
        //shoot();
    }
	obj_ptr->setVelocity(velocity);
	obj_ptr->playAnimation(aNum);
}
std::shared_ptr<DynamicGameObject> Player::getObject()
{
	return obj_ptr;
}
void Player::shoot(sf::RenderWindow& window)
{
	sf::Time time = clock.getElapsedTime();
	if (time > shootfreq) {
    	auto bullet = oManager.newDynamicObject(2);
    	sf::Vector2f pos = obj_ptr->getPosition();
    	pos.x += 16;
    	pos.y += 16;
    	bullet->setPosition(pos);
    	sf::Mouse mouse;
    	sf::Vector2i mouse_pos = mouse.getPosition(window);
		auto new_mouse_pos = window.mapPixelToCoords(mouse_pos);
    	bullet->setVelocity(1000.f * getNormalized(sf::Vector2f(new_mouse_pos.x - pos.x, new_mouse_pos.y - pos.y)));
		bullet->setSlowMode(false);
		float angle = atan((new_mouse_pos.y - pos.y) / (new_mouse_pos.x - pos.x)) * 180.f / PI;
    	bullet->setRotation(angle);
		clock.restart();
	}
}
sf::Vector2f Player::getPosition() const
{
	return obj_ptr->getPosition();
}
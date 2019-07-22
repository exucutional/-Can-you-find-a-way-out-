#include "gameobjects.hpp"
static const float SLOW_RATE = 10;
static const float SPEED_RATE = 200;
void GameObject::addAnimation(std::shared_ptr<Animation> animation_ptr, std::size_t num) 
{
	assert(animation_ptr);
	if (num < AnimationTypeSize)
		animationVec[num] = animation_ptr;
	else
		assert(0);
}
void GameObject::setAnimation(std::size_t num)
{
	assert(animationVec[num]);
	currentAnimationNum = num;
	aManager.setAnimation(*animationVec[num].get());
}
void GameObject::playAnimation(std::size_t num)
{
	assert(animationVec[num]);
	currentAnimationNum = num;
	aManager.play(*animationVec[num].get());
}
const Animation* GameObject::getAnimation(std::size_t num) const 
{
	if (num < AnimationTypeSize)
		return animationVec[num].get();
	return nullptr;
}
std::size_t GameObject::getCurrentAnimationNum() const
{
	return currentAnimationNum;
}
void GameObject::render(sf::RenderTarget& target, sf::Time frameTime)
{
	aManager.play();
	aManager.update(frameTime);
	sf::FloatRect fRect = aManager.getGlobalBounds();
	collider.setRectPosition(fRect.left, fRect.top);
	sf::Vector2f size(fRect.width, fRect.height);
	collider.setRectSize(size);
	target.draw(aManager);
	target.draw(collider.getInfo());
	target.draw(collider.getRect());
}
void GameObject::setPosition(float x, float y)
{
	aManager.setPosition(x, y);
}
void GameObject::setPosition(const sf::Vector2f& position)
{
	aManager.setPosition(position);
}
void GameObject::move(const sf::Vector2f& vec)
{
	aManager.move(vec);
	sf::FloatRect fRect = aManager.getGlobalBounds();
	collider.setRectPosition(fRect.left, fRect.top);
	sf::Vector2f size(fRect.width, fRect.height);
	collider.setRectSize(size);
	collider.setConvexPoint(0, sf::Vector2f(fRect.left, fRect.top));
	collider.setConvexPoint(1, sf::Vector2f(fRect.left + fRect.width, fRect.top));
	collider.setConvexPoint(2, sf::Vector2f(fRect.left + fRect.width, fRect.top + fRect.height));
	collider.setConvexPoint(3, sf::Vector2f(fRect.left, fRect.top + fRect.height));
}
const Collider& GameObject::getCollider() const
{
	return collider;
}
std::size_t GameObject::getType() const
{
	return type;
}
void GameObject::setType(std::size_t type_)
{
	type = type_;
}
GameObject& GameObject::getRef()
{
	return std::ref(*this);
}
StaticGameObject& StaticGameObject::getRef()
{
	return std::ref(*this);
}
DynamicGameObject::DynamicGameObject(sf::Vector2f velocity_):
velocity(velocity_)
{
	__DEBUG_EXEC(std::cout << "DynamicGameObject(std::vector<float>)\n");
	collider.setConvexPointCount(4);
}
DynamicGameObject::~DynamicGameObject()
{
	__DEBUG_EXEC(std::cout << "~DynamicGameObject()\n");
}

void DynamicGameObject::setVelocity(const sf::Vector2f& velocity_)
{
	velocity = velocity_;
}
sf::Vector2f DynamicGameObject::getVelocity() const
{
	return velocity;
}
void DynamicGameObject::update()
{
	float velx = velocity.x;
	float vely = velocity.y;
	if (velx) {
		if (velx > SLOW_RATE)
			velocity.x = velx - SLOW_RATE;
		else
		if (velx < -SLOW_RATE) 
			velocity.x = velx + SLOW_RATE;
		else 
			velocity.x = 0;
	}
	if (vely) {
		if (vely > SLOW_RATE)
			velocity.y = vely - SLOW_RATE;
		else
		if (vely < -SLOW_RATE) 
			velocity.y = vely + SLOW_RATE;
		else 
			velocity.y = 0;
	}
	aManager.move(velocity.x * deltaTime.asSeconds(), velocity.y * deltaTime.asSeconds());
	sf::FloatRect fRect = aManager.getGlobalBounds();
	collider.setRectPosition(fRect.left, fRect.top);
	sf::Vector2f size(fRect.width, fRect.height);
	collider.setRectSize(size);
	collider.setConvexPoint(0, sf::Vector2f(fRect.left, fRect.top));
	collider.setConvexPoint(1, sf::Vector2f(fRect.left + fRect.width, fRect.top));
	collider.setConvexPoint(2, sf::Vector2f(fRect.left + fRect.width, fRect.top + fRect.height));
	collider.setConvexPoint(3, sf::Vector2f(fRect.left, fRect.top + fRect.height));
}
void DynamicGameObject::render(sf::RenderTarget& target, sf::Time frameTime)
{
	if (velocity.x != 0 || velocity.y != 0)
		aManager.play();
	else
		aManager.stop();
	aManager.update(frameTime);
	target.draw(aManager);
	target.draw(collider.getInfo());
	target.draw(collider.getRect());
}
DynamicGameObject& DynamicGameObject::getRef()
{
	return std::ref(*this);
}
Player::Player()
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
	obj_ptr->setVelocity(velocity);
	obj_ptr->playAnimation(aNum);
}
std::shared_ptr<DynamicGameObject> Player::getObject()
{
	return obj_ptr;
}

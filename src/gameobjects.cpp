#include "gameobjects.hpp"
void GameObject::addAnimation(std::shared_ptr<const Animation> animation_ptr, std::size_t num) 
{
	if (num < AnimationTypeSize)
		animationVec[num] = animation_ptr;
}
void GameObject::setAnimation(const Animation* animation_ptr)
{
	aManager.setAnimation(*animation_ptr);
}
const Animation* GameObject::getAnimation(std::size_t num) const 
{
	if (num < AnimationTypeSize)
		return animationVec[num].get();
	return nullptr;
}
void GameObject::render(sf::RenderTarget& target, sf::Time frameTime)
{
	aManager.play();
	aManager.update(frameTime);
	sf::FloatRect fRect = aManager.getGlobalBounds();
	collision.collider.setOBBposition(fRect.left, fRect.top);
	sf::Vector2f size(fRect.width, fRect.height);
	collision.collider.setOBBsize(size);
	target.draw(aManager);
	target.draw(collision.collider.getInfo());
	target.draw(collision.collider.getOBB());
}
void GameObject::setPosition(float x, float y)
{
	aManager.setPosition(x, y);
}
void GameObject::setPosition(const sf::Vector2f& position)
{
	aManager.setPosition(position);
}
DynamicGameObject::DynamicGameObject(std::vector<float> velocity_):
velocity(velocity_)
{
	__DEBUG_EXEC(std::cout << "DynamicGameObject(std::vector<float>)\n");
}
DynamicGameObject::~DynamicGameObject()
{
	__DEBUG_EXEC(std::cout << "~DynamicGameObject()\n");
}

void DynamicGameObject::setVelocity(std::vector<float> velocity_)
{
	velocity = velocity_;
}
const std::vector<float> DynamicGameObject::getVelocity() const
{
	return velocity;
}
void DynamicGameObject::control()
{
	int aNum = aDown;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
		aNum = aDown;
		velocity[1] = 100.f;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
		aNum = aUp;
		velocity[1] = -100.f;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
		aNum = aLeft;
		velocity[0] = -100.f;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
		aNum = aRight;
		velocity[0] = 100.f;
	}
	aManager.play(*animationVec[aNum]);
}
void DynamicGameObject::update()
{
	float velx = velocity[0];
	float vely = velocity[1];
	if (velx)
		velocity[0] -= (velx > 0) ? 2 : -2;
	if (vely)
		velocity[1] -= (vely > 0) ? 2 : -2;
}
void DynamicGameObject::render(sf::RenderTarget& target, sf::Time frameTime)
{
	if (velocity[0] != 0 || velocity[1] != 0)
		aManager.play();
	else
		aManager.stop();
	aManager.move(velocity[0] * deltaTime.asSeconds(), velocity[1] * deltaTime.asSeconds());
	aManager.update(frameTime);
	update();
	target.draw(aManager);
	sf::FloatRect fRect = aManager.getGlobalBounds();
	collision.collider.setOBBposition(fRect.left, fRect.top);
	sf::Vector2f size(fRect.width, fRect.height);
	collision.collider.setOBBsize(size);
	target.draw(aManager);
	target.draw(collision.collider.getInfo());
	target.draw(collision.collider.getOBB());
}
void Player::setObject(DynamicGameObject* obj_ptr_)
{
	obj_ptr = std::shared_ptr<DynamicGameObject>(obj_ptr_);
}
void Player::setObject(std::shared_ptr<DynamicGameObject> obj_ptr_)
{
	obj_ptr = obj_ptr_;
}
void Player::control()
{
	obj_ptr->control();
}


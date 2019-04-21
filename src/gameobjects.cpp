#include "gameobjects.hpp"
void Player::setObject(DynamicGameObject* object)
{
	managedObject = object;
}
void Player::control()
{
	managedObject->control();
}
void GameObject::addAnimation(const Animation* animation, std::size_t num) 
{
	if (num < AnimationTypeSize)
		animationVec[num] = animation;
}
void GameObject::setAnimation(const Animation* animation)
{
	aManager.setAnimation(*animation);
}
const Animation* GameObject::getAnimation(std::size_t num) const 
{
	if (num < AnimationTypeSize)
		return animationVec[num];
	return nullptr;
}
void GameObject::render(sf::RenderTarget& target, sf::Time frameTime)
{
	aManager.play();
	aManager.update(frameTime);
	target.draw(aManager);
}
void GameObject::setPosition(float x, float y)
{
	aManager.setPosition(x, y);
}
void GameObject::setPosition(const sf::Vector2f& position)
{
	aManager.setPosition(position);
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
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
		aManager.play(*animationVec[aDown]);
		velocity[1] = 100.f;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
		aManager.play(*animationVec[aLeft]);
		velocity[0] = -100.f;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
		aManager.play(*animationVec[aUp]);
		velocity[1] = -100.f;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
		aManager.play(*animationVec[aRight]);
		velocity[0] = 100.f;
	}
}
void DynamicGameObject::update()
{
	float velx = velocity[0];
	float vely = velocity[1];
	if (velx)
		velocity[0] -= (velx > 0) ? 1 : -1;
	if (vely)
		velocity[1] -= (vely > 0) ? 1 : -1;
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
}



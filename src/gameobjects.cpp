#include "gameobjects.hpp"
static const float SLOW_RATE = 10;
GameObject::GameObject():
	type(0),
	currentAnimationNum(0),
	isActive_(true)
{
	collider.setConvexPointCount(4);
}
GameObject::GameObject(const GameObject& obj):
	type(obj.type),
	currentAnimationNum(obj.currentAnimationNum),
	isActive_(true)
{
	collider.setConvexPointCount(4);
	animationVec = obj.animationVec;
	aManager = obj.aManager;
	sf::FloatRect fRect = aManager.getLocalBounds();
	collider.setRect(fRect);
	setAnimation(currentAnimationNum);
}
GameObject::GameObject(GameObject&& obj):
	type(obj.type),
	currentAnimationNum(obj.currentAnimationNum),
	isActive_(true)
{
	collider.setConvexPointCount(4);
	animationVec = std::move(obj.animationVec);
	aManager = std::move(obj.aManager);
	sf::FloatRect fRect = aManager.getLocalBounds();
	collider.setRect(fRect);
	setAnimation(currentAnimationNum);
}
GameObject& GameObject::operator=(const GameObject& obj)
{
	collider.setConvexPointCount(4);
	type = obj.type; 
	currentAnimationNum = obj.currentAnimationNum;
	isActive_ = true;
	animationVec = obj.animationVec;
	aManager = obj.aManager;
	sf::FloatRect fRect = aManager.getLocalBounds();
	collider.setRect(fRect);
	setAnimation(currentAnimationNum);
	return *this;
}
GameObject& GameObject::operator=(GameObject&& obj)
{
	collider.setConvexPointCount(4);
	type = obj.type; 
	currentAnimationNum = obj.currentAnimationNum;
	isActive_ = true;
	animationVec = std::move(obj.animationVec);
	aManager = std::move(obj.aManager);
	sf::FloatRect fRect = aManager.getLocalBounds();
	collider.setRect(fRect);	
	setAnimation(currentAnimationNum);
	return *this;
}
void GameObject::addAnimation(std::shared_ptr<Animation> animation_ptr, std::size_t num) 
{
	assert(animation_ptr);
	assert(num < AnimationTypeSize);
	animationVec[num] = animation_ptr;
	sf::IntRect iRect = animation_ptr->getFrame(0);
	collider.setRect(iRect);
}
void GameObject::setAnimation(std::size_t num)
{
	assert(animationVec[num]);
	currentAnimationNum = num;
	//float angle = aManager.getRotation();
	aManager.setAnimation(*animationVec[num].get());
	//sf::FloatRect fRect = aManager.getGlobalBounds();
	//collider.setRectPosition(fRect.left, fRect.top);
	//sf::Vector2f size(fRect.width, fRect.height);
	//collider.setRectSize(size);
	//collider.setConvexPoint(0, sf::Vector2f(fRect.left, fRect.top));
	//collider.setConvexPoint(1, sf::Vector2f(fRect.left + fRect.width, fRect.top));
	//collider.setConvexPoint(2, sf::Vector2f(fRect.left + fRect.width, fRect.top + fRect.height));
	//collider.setConvexPoint(3, sf::Vector2f(fRect.left, fRect.top + fRect.height));
	//aManager.setRotation(angle);
	//collider.setRotation(angle);
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
	//sf::FloatRect fRect = aManager.getGlobalBounds();
	//collider.setRectPosition(fRect.left, fRect.top);
	//sf::Vector2f size(fRect.width, fRect.height);
	//collider.setRectSize(size);
	target.draw(aManager);
	target.draw(collider.getInfo());
	target.draw(collider.getRect());
}
void GameObject::setPosition(float x, float y)
{
	aManager.setPosition(x, y);
	collider.setRectPosition(x, y);
	collider.setConvexPosition(x, y);
}
void GameObject::setPosition(const sf::Vector2f& position)
{
	aManager.setPosition(position);
	collider.setRectPosition(position);
	collider.setConvexPosition(position);
}
sf::Vector2f GameObject::getPosition() const 
{
	return aManager.getPosition();
}
void GameObject::setRotation(float angle)
{
	aManager.setRotation(angle);
	collider.setRotation(angle);
}
void GameObject::move(const sf::Vector2f& vec)
{
	aManager.move(vec);
	collider.move(vec);
	/* 
	sf::FloatRect fRect = aManager.getGlobalBounds();
	collider.setRectPosition(fRect.left, fRect.top);
	sf::Vector2f size(fRect.width, fRect.height);
	collider.setRectSize(size);
	collider.setConvexPoint(0, sf::Vector2f(fRect.left, fRect.top));
	collider.setConvexPoint(1, sf::Vector2f(fRect.left + fRect.width, fRect.top));
	collider.setConvexPoint(2, sf::Vector2f(fRect.left + fRect.width, fRect.top + fRect.height));
	collider.setConvexPoint(3, sf::Vector2f(fRect.left, fRect.top + fRect.height));*/
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
void GameObject::activate()
{
	isActive_ = true;
}
void GameObject::deactivate()
{
	isActive_ = false;
}
bool GameObject::isActive() const 
{
	return isActive_;
}
void GameObject::setOrigin(float x, float y)
{
	aManager.setOrigin(x, y);
	collider.setOrigin(x, y);
}
void GameObject::setOrigin(sf::Vector2f vec)
{
	aManager.setOrigin(vec);
	collider.setOrigin(vec);
}
StaticGameObject& StaticGameObject::getRef()
{
	return std::ref(*this);
}
DynamicGameObject::DynamicGameObject(sf::Vector2f velocity_):
	velocity(velocity_),
	slowmode(true)
{
	__DEBUG_EXEC(std::cout << "DynamicGameObject(std::vector<float>)\n");
}
DynamicGameObject::DynamicGameObject(const DynamicGameObject& obj):
	GameObject(obj),
	velocity(obj.velocity),
	slowmode(obj.slowmode)
{
	__DEBUG_EXEC(std::cout << "DynamicGameObject(copy)\n");
}
DynamicGameObject::DynamicGameObject(DynamicGameObject&& obj):
	GameObject(obj),
	slowmode(obj.slowmode)
{
	__DEBUG_EXEC(std::cout << "DynamicGameObject(move)\n");
	velocity = std::move(obj.velocity);
}
DynamicGameObject& DynamicGameObject::operator=(const DynamicGameObject& obj)
{
	collider.setConvexPointCount(4);
	setType(obj.getType());
	activate();
	setSlowMode(obj.getSlowMode());
	animationVec = obj.animationVec;
	aManager = obj.aManager;
	return *this;
}
DynamicGameObject& DynamicGameObject::operator=(DynamicGameObject&& obj)
{
	collider.setConvexPointCount(4);
	setType(obj.getType());
	activate();
	setSlowMode(obj.getSlowMode());
	animationVec = std::move(obj.animationVec);
	aManager = std::move(obj.aManager);
	return *this;
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
void DynamicGameObject::setSlowMode(bool slowmode_)
{
	slowmode = slowmode_;
}
bool DynamicGameObject::getSlowMode() const
{
	return slowmode;
}
void DynamicGameObject::update()
{
	if (slowmode) {
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
	}
	aManager.move(velocity.x * deltaTime.asSeconds(), velocity.y * deltaTime.asSeconds());
	collider.move(velocity.x * deltaTime.asSeconds(), velocity.y * deltaTime.asSeconds());
	/* sf::FloatRect fRect = aManager.getGlobalBounds();
	collider.setRectPosition(fRect.left, fRect.top);
	sf::Vector2f size(fRect.width, fRect.height);
	collider.setRectSize(size);
	collider.setConvexPoint(0, sf::Vector2f(fRect.left, fRect.top));
	collider.setConvexPoint(1, sf::Vector2f(fRect.left + fRect.width, fRect.top));
	collider.setConvexPoint(2, sf::Vector2f(fRect.left + fRect.width, fRect.top + fRect.height));
	collider.setConvexPoint(3, sf::Vector2f(fRect.left, fRect.top + fRect.height));
	*/
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
	//target.draw(collider.getRect());
	target.draw(collider.getConvex());
}
DynamicGameObject& DynamicGameObject::getRef()
{
	return std::ref(*this);
}
#ifndef GAMEOBJECT_HPP_
#define GAMEOBJECT_HPP_
#include <SFML/Graphics.hpp>
#include <vector>
#include <memory>
#include "animation.hpp"
#include "collision.hpp"
#include "interaction.hpp"
extern const sf::Time deltaTime;
#ifndef NDEBUG
#define __DEBUG_EXEC(code) code
#else
#define __DEBUG_EXEC(code) ;
#endif
enum AnimationType {
	aDown = 0,
	aLeft,
	aUp,
	aRight,
	AnimationTypeSize
};
class GameObject
{
	std::size_t type;
	std::size_t currentAnimationNum;
protected:
	std::vector<std::shared_ptr<const Animation>> animationVec = std::vector<std::shared_ptr<const Animation>>(AnimationTypeSize);
	Collider collider;
	AnimationManager aManager;
public:
	GameObject(): 
	type(0),
	currentAnimationNum(0)
	{}
	virtual ~GameObject() {}
	void addAnimation(std::shared_ptr<Animation> animation_ptr, std::size_t num);
	void setAnimation(std::size_t num);
	void playAnimation(std::size_t num);
	const Animation* getAnimation(std::size_t num) const;
	std::size_t getCurrentAnimationNum() const;
	void setPosition(float x, float y);
	void setPosition(const sf::Vector2f& position);
	void move(const sf::Vector2f& vec);
	//virtual void setVelocity(const sf::Vector2f& velocity_) {}
	virtual void render(sf::RenderTarget& target, sf::Time frameTime);
	const Collider& getCollider() const;
	std::size_t getType() const;
	void setType(std::size_t type);
	virtual GameObject& getRef();
};
class StaticGameObject : public GameObject
{
public:
	virtual StaticGameObject& getRef();
};
class DynamicGameObject : public GameObject
{
	sf::Vector2f velocity;
public:
	DynamicGameObject(sf::Vector2f velocity_ = {0, 0});
	~DynamicGameObject();
	void setVelocity(const sf::Vector2f& velocity_);
	sf::Vector2f getVelocity() const;
	void render(sf::RenderTarget& target, sf::Time frameTime);
	void update();
	virtual DynamicGameObject& getRef();
};
class Player
{
	std::shared_ptr<DynamicGameObject> obj_ptr;
public:
	Player();
	~Player();
	void setObject(DynamicGameObject* obj_ptr);
	void setObject(std::shared_ptr<DynamicGameObject> obj_ptr);
	std::shared_ptr<DynamicGameObject> getObject();
	void control();
};
#endif //GAMEOBJECT_HPP_
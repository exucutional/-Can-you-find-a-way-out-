#ifndef GAMEOBJECT_HPP_
#define GAMEOBJECT_HPP_
#include <SFML/Graphics.hpp>
#include <vector>
#include <memory>
#include "animation.hpp"
#include "collision.hpp"
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
protected:
	std::vector<std::shared_ptr<const Animation>> animationVec = std::vector<std::shared_ptr<const Animation>>(AnimationTypeSize);
	Collision collision;
	AnimationManager aManager;
public:
	GameObject() {}
	virtual ~GameObject() {}
	void addAnimation(std::shared_ptr<Animation> animation_ptr, std::size_t num);
	void setAnimation(std::size_t num);
	const Animation* getAnimation(std::size_t num) const;
	void setPosition(float x, float y);
	void setPosition(const sf::Vector2f& position);
	virtual void render(sf::RenderTarget& target, sf::Time frameTime);
};
class StaticGameObject : public GameObject
{
};
class DynamicGameObject : public GameObject
{
	std::vector<float> velocity;
public:
	DynamicGameObject(std::vector<float> velocity_ = {0, 0});
	~DynamicGameObject();
	void setVelocity(std::vector<float> velocity_);
	const std::vector<float> getVelocity() const;
	virtual void render(sf::RenderTarget& target, sf::Time frameTime);
	void update();
	void control();
};
class Player
{
	std::shared_ptr<DynamicGameObject> obj_ptr;
public:
	Player(): obj_ptr(nullptr) {};
	void setObject(DynamicGameObject* obj_ptr);
	void setObject(std::shared_ptr<DynamicGameObject> obj_ptr);
	std::shared_ptr<DynamicGameObject> getObject();
	void control();
};
#endif //GAMEOBJECT_HPP_
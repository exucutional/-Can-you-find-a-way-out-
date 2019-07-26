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
	bool isActive_;
protected:
	std::vector<std::shared_ptr<const Animation>> animationVec = std::vector<std::shared_ptr<const Animation>>(AnimationTypeSize);
	Collider collider;
	AnimationManager aManager;
public:
	GameObject();
	GameObject(const GameObject& obj);
	GameObject(GameObject&& obj);
	GameObject& operator=(const GameObject& obj);
	GameObject& operator=(GameObject&& obj);
	virtual ~GameObject() {}
	void addAnimation(std::shared_ptr<Animation> animation_ptr, std::size_t num);
	void setAnimation(std::size_t num);
	void playAnimation(std::size_t num);
	const Animation* getAnimation(std::size_t num) const;
	std::size_t getCurrentAnimationNum() const;
	void setPosition(float x, float y);
	void setPosition(const sf::Vector2f& position);
	sf::Vector2f getPosition() const;
	void setRotation(float angle);
	void setOrigin(float x, float y);
	void setOrigin(sf::Vector2f vec);
	void move(const sf::Vector2f& vec);
	virtual void render(sf::RenderTarget& target, sf::Time frameTime);
	const Collider& getCollider() const;
	std::size_t getType() const;
	void setType(std::size_t type);
	void activate();
	void deactivate();
	bool isActive() const;
	virtual GameObject& getRef();
};
class StaticGameObject : public GameObject
{
public:
	using GameObject::GameObject;
	virtual StaticGameObject& getRef();
};
class DynamicGameObject : public GameObject
{
	sf::Vector2f velocity;
	bool slowmode;
public:
	DynamicGameObject(sf::Vector2f velocity_ = {0, 0});
	DynamicGameObject(const DynamicGameObject& obj);
	DynamicGameObject(DynamicGameObject&& obj);
	DynamicGameObject& operator=(const DynamicGameObject& obj);
	DynamicGameObject& operator=(DynamicGameObject&& obj);
	~DynamicGameObject();
	void setVelocity(const sf::Vector2f& velocity_);
	void setSlowMode(bool slowmode);
	bool getSlowMode() const;
	sf::Vector2f getVelocity() const;
	void render(sf::RenderTarget& target, sf::Time frameTime);
	void update();
	virtual DynamicGameObject& getRef();
};
#endif //GAMEOBJECT_HPP_
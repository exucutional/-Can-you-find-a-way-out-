#ifndef GAMEOBJECT_HPP_
#define GAMEOBJECT_HPP_
#include <SFML/Graphics.hpp>
#include <vector>
#include <memory>
#include "animation.hpp"
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
/*
template <typename T>
struct std::vector<float>tor
{
	T x, y;
	std::vector<float>tor() : x (0), y (0) {}
	template <typename U1, typename U2>
	std::vector<float>tor (U1 x, U2 y) : x ((T) x), y ((T) y) {}
	template <typename U>
	std::vector<float>tor (const std::vector<float>tor <U>& std::vector<float>) : x ((T) std::vector<float>.x), y ((T) std::vector<float>.y) {}
	template <typename U>
	std::vector<float>tor (const sf::std::vector<float>tor2 <U>& std::vector<float>) : x ((T) std::vector<float>.x), y ((T) std::vector<float>.y) {}
};
using std::vector<float> = std::vector<float>tor <float>;
*/
class GameObject
{
protected:
	std::vector<std::shared_ptr<const Animation>> animationVec = std::vector<std::shared_ptr<const Animation>>(AnimationTypeSize);
	AnimationManager aManager;
public:
	GameObject() {}
	virtual ~GameObject() {}
	void addAnimation(std::shared_ptr<const Animation> animation_ptr, std::size_t num);
	void setAnimation(const Animation* animation_ptr);
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
	DynamicGameObject* managedObject;
public:
	Player(): managedObject(nullptr) {};
	void setObject(DynamicGameObject* object);
	void control();
};
#endif //GAMEOBJECT_HPP_
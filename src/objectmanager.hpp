#ifndef OBJECTMANAGER_HPP_
#define OBJECTMANAGER_HPP_
#include <SFML/Graphics.hpp>
#include <vector>
#include <memory>
class ObjectManager
{
	std::vector<GameObject*> objVec;
public:
	ObjectManager();
	~ObjectManager();
	void addObject(GameObject* newObj);
	const GameObject* getObject(std::size_t num) const;
	const std::size_t getSize() const;
	void render(sf::RenderTarget& target, sf::Time frameTime);
};
#endif //OBJECTMANAGER_HPP_
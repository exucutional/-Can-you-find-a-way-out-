#ifndef OBJECTMANAGER_HPP_
#define OBJECTMANAGER_HPP_
#include <SFML/Graphics.hpp>
#include <vector>
#include <memory>
class ObjectManager
{
	std::vector<std::shared_ptr<GameObject>> objVec;
public:
	ObjectManager();
	~ObjectManager();
	template<typename T, typename... Args>
	std::shared_ptr<T> create(Args... args) {
		auto obj_ptr = std::make_shared<T>(args...);
		objVec.push_back(obj_ptr);
		return obj_ptr;
	}
	void addObject(GameObject* obj_ptr);
	void addObject(std::shared_ptr<GameObject> obj_ptr);
	std::shared_ptr<GameObject> getObject(std::size_t num) const;
	const std::size_t getSize() const;
	void render(sf::RenderTarget& target, sf::Time frameTime);
};
#endif //OBJECTMANAGER_HPP_
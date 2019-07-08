#ifndef STATEMANAGER_HPP_
#define STATEMANAGER_HPP_
#include <SFML/Graphics.hpp>
#include <vector>
#include <map>
#include <memory>
class StateManager
{
	std::vector<std::unique_ptr<State>> statVec;
	std::size_t currentStateIndex;
public:
	StateManager(sf::RenderWindow& window, AssetManager& asManager);
	~StateManager();
	void addState(State* state_ptr);
	//const State& getState(std::size_t index) const;
	//const State& getCurrentState() const;
	//std::size_t getCurrentStateIndex() const;
	int setState(std::size_t index);
};
#endif //STATEMANAGER_HPP_
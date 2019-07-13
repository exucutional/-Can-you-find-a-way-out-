#include "game.hpp"
AssetManager::AssetManager()
{
    __DEBUG_EXEC(std::cout << "AssetManager()\n");
}
AssetManager::~AssetManager()
{
    __DEBUG_EXEC(std::cout << "~AssetManager()\n");
}
StateManager::StateManager(sf::RenderWindow& window, AssetManager& asManager)
{
    __DEBUG_EXEC(std::cout << "StateManager(sf::RenderWindow&, AssetManager&)\n");
    statVec.push_back(std::move(std::unique_ptr<MenuState>(new MenuState(window, asManager))));
    statVec.push_back(std::move(std::unique_ptr<GameState>(new GameState(window, asManager))));
    currentStateIndex = MENU_STATE;
}
StateManager::~StateManager()
{
    __DEBUG_EXEC(std::cout << "~StateManager()\n");
}
void StateManager::addState(State* state_ptr)
{
    if (state_ptr)
        statVec.push_back(std::move(std::unique_ptr<State>(state_ptr)));
}
int StateManager::setState(std::size_t index)
{
    State* state_ptr = statVec[index].get();
    if (state_ptr) {
        currentStateIndex = index;
        state_ptr->resume();
        return state_ptr->gameLoop();
    }
    currentStateIndex = CLOSED_STATE;
    fprintf(stderr, "State do not exist\n");
    return CLOSED_STATE;
}
ObjectManager::ObjectManager()
{
    __DEBUG_EXEC(std::cout << "ObjectManager()\n");
}
ObjectManager::~ObjectManager() 
{
    __DEBUG_EXEC(std::cout << "~ObjectManager()\n");
}
void ObjectManager::addObject(GameObject* obj_ptr)
{
    objVec.push_back(std::shared_ptr<GameObject>(obj_ptr));
}
void ObjectManager::addObject(std::shared_ptr<GameObject> obj_ptr)
{
    objVec.push_back(obj_ptr);
}
std::shared_ptr<GameObject> ObjectManager::getObject(std::size_t num) const
{
    if (num <= objVec.size())
        return objVec[num];
    return nullptr;
}
const std::size_t ObjectManager::getSize() const
{
    return objVec.size();
}
void ObjectManager::render(sf::RenderTarget& target, sf::Time frameTime)
{
    for (auto obj: objVec) {
        if (obj)
            obj->render(target, frameTime);
    }
}
App::App() 
:asManager(),
sManager(window, asManager)
{
    __DEBUG_EXEC(std::cout << "App()\n");
    LuaScript script("data/setting.lua");
    int width = script.get<int>("Window.Screen_resolution.width");
    int height = script.get<int>("Window.Screen_resolution.height");
    sf::Vector2i screenDimensions(width, height);
    window.create(sf::VideoMode(screenDimensions.x, screenDimensions.y), "animation test");
    window.setFramerateLimit(144);
}
App::~App()
{
    __DEBUG_EXEC(std::cout << "~App()\n");
}
int App::run()
{   
    int nextStateIndex = GAME_STATE;
    while ((nextStateIndex = sManager.setState(nextStateIndex)) != CLOSED_STATE);
    return EXIT_SUCCESS;
}
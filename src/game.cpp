#include "game.hpp"
static const float REPULSION_RATE = 50;
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
std::shared_ptr<DynamicGameObject> ObjectManager::newDynamicObject(std::size_t type)
{
    for (auto& obj: dynObjVec) {
        if (obj->getType() == type && !obj->isActive()) {
            obj->activate();
            return obj;
        }
    }
    for (auto& obj: typeObjVec) {
        if (obj->getType() == type) {
            auto obj_ptr =  std::make_shared<DynamicGameObject>(static_cast<DynamicGameObject&>(*obj));
            dynObjVec.push_back(obj_ptr);
            return obj_ptr;
        }
    }
    std::cerr << "_____ERROR: Dynamic object type " << type << " is uninitialized\n";
    return nullptr;
}
std::shared_ptr<StaticGameObject> ObjectManager::newStaticObject(std::size_t type)
{
    for (auto& obj: stObjVec) {
        if (obj->getType() == type && !obj->isActive()) {
            obj->activate();
            return obj;
        }
    }
    for (auto& obj: typeObjVec) {
        if (obj->getType() == type) {
            auto obj_ptr =  std::make_shared<StaticGameObject>(static_cast<StaticGameObject&>(*obj));
            stObjVec.push_back(obj_ptr);
            return obj_ptr;
        }
    }
    std::cerr << "_____ERROR: Static object type " << type << " is uninitialized\n";
    return nullptr;
}
std::shared_ptr<DynamicGameObject> ObjectManager::findDynamicObject(std::size_t type) 
{
    for (auto& obj: dynObjVec) {
        if (obj->getType() == type && obj->isActive())
            return obj;
    }
    return nullptr;
}
std::shared_ptr<StaticGameObject> ObjectManager::findStaticObject(std::size_t type) 
{
    for (auto& obj: stObjVec) {
        if (obj->getType() == type && obj->isActive())
            return obj;
    }
    return nullptr;
}
void ObjectManager::addDynamicObject(std::shared_ptr<DynamicGameObject> obj_ptr)
{
    assert(obj_ptr);
    dynObjVec.push_back(obj_ptr);
}
void ObjectManager::addStaticObject(std::shared_ptr<StaticGameObject> obj_ptr)
{
    assert(obj_ptr);
    stObjVec.push_back(obj_ptr);
}
std::shared_ptr<DynamicGameObject> ObjectManager::getDynObject(std::size_t num) const
{
    if (num <= dynObjVec.size())
        return dynObjVec[num];
    return nullptr;
}
std::shared_ptr<StaticGameObject> ObjectManager::getStObject(std::size_t num) const
{
    if (num <= stObjVec.size())
        return stObjVec[num];
    return nullptr;
}
const std::size_t ObjectManager::getDynSize() const
{
    return dynObjVec.size();
}
const std::size_t ObjectManager::getStSize() const
{
    return stObjVec.size();
}
void ObjectManager::render(sf::RenderTarget& target, sf::Time frameTime)
{
    for (auto& obj: dynObjVec) {
        if (obj && obj->isActive())
            obj->render(target, frameTime);
    }
    for (auto& obj: stObjVec) {
        if (obj && obj->isActive())
            obj->render(target, frameTime);
    }
}
void ObjectManager::interact()
{
    auto size = dynObjVec.size();
    sf::Vector2f mtv;
    sf::Vector2f* mtv_ptr = &mtv;
    for (std::size_t i = 0; i < size - 1; i++) {
        for (std::size_t j = i + 1; j < size; j++) {
            if (dynObjVec[i]->isActive() && dynObjVec[j]->isActive())
                if (collision.isCollide(dynObjVec[i]->getCollider(), dynObjVec[j]->getCollider(), CONVEX_MODE, mtv_ptr)) {
                    intManager.interact(*dynObjVec[i], *dynObjVec[j], mtv);
                    intManager.interact(*dynObjVec[j], *dynObjVec[i], -mtv);
            }
        }
    }
}
void ObjectManager::update()
{
    for (auto& obj: dynObjVec) {
        if (obj && obj->isActive())
            obj->update();
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
    bool fullScreen = script.get<bool>("Window.FullScreen");
    sf::Vector2i screenDimensions(width, height);
    if (fullScreen)
        window.create(sf::VideoMode(screenDimensions.x, screenDimensions.y), "view test", sf::Style::Fullscreen);
    else
        window.create(sf::VideoMode(screenDimensions.x, screenDimensions.y), "view test");
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
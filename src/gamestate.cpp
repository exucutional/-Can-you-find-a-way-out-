#include "state.hpp"
GameState::GameState(sf::RenderWindow& window_, AssetManager& asManager_):
State(window_, asManager_)
{
	nextStateIndex = GAME_STATE;
	isPaused = false;
	__DEBUG_EXEC(std::cout << "GameState(sf::RenderWindow&, AssetManager&)\n");
	init();
}
GameState::~GameState()
{
	__DEBUG_EXEC(std::cout << "~GameState()\n");
}
void GameState::init()
{
    sol::state lua;
    lua.open_libraries(sol::lib::base, sol::lib::package);
    lua.new_usertype<AssetManager>("AssetManager", sol::constructors<AssetManager()>(),
        "createTexture", &AssetManager::createTexture<>,
        "createAnimation", &AssetManager::createAnimation<>);
    lua.new_usertype<ObjectManager>("ObjectManager", sol::constructors<ObjectManager()>(),
        "createDynamicGameObject", &ObjectManager::createDynamicObject<>);
    lua.new_usertype<Animation>("Animation", sol::constructors<Animation()>(),
        "setSpriteSheet", sol::resolve<void(std::shared_ptr<sf::Texture>)>(&Animation::setSpriteSheet),
        "addFrame", &Animation::addFrame);
    lua.new_usertype<sf::Texture>("Texture", sol::constructors<sf::Texture(), sf::Texture(const sf::Texture&)>(),
        "loadFromFile", &sf::Texture::loadFromFile,
        "create", &sf::Texture::create);    
    lua.new_usertype<sf::IntRect>("IntRect", sol::constructors<sf::IntRect(), sf::IntRect(int, int, int, int)>());
    lua.new_usertype<GameObject>("GameObject", sol::constructors<GameObject()>(),
        "addAnimation", &GameObject::addAnimation,
        "setAnimation", &GameObject::setAnimation,
        "getAnimation", &GameObject::getAnimation,
        "setType", &GameObject::setType,
        "setPosition", sol::overload(
            sol::resolve<void(float, float)>(&GameObject::setPosition),
            sol::resolve<void(const sf::Vector2f&)>(&GameObject::setPosition)));
    lua.new_usertype<DynamicGameObject>("DynamicGameObject", sol::constructors<DynamicGameObject()>(),
        sol::base_classes, sol::bases<GameObject>());
    lua.new_usertype<Player>("Player", sol::constructors<Player()>(),
        "setObject", sol::resolve<void(std::shared_ptr<DynamicGameObject>)>(&Player::setObject));
    lua["asManager"] = std::ref(asManager); 
    lua["oManager"] = std::ref(oManager);
    lua["player"] = std::ref(player);
    lua["aDown"] = aDown;
    lua["aLeft"] = aLeft;
    lua["aRight"] = aRight;
    lua["aUp"] = aUp;
    lua.script_file("scripts/gamestate_init.lua");
}
void GameState::pause()
{
	isPaused = true;
}
void GameState::resume()
{
	isPaused = false;
}
void GameState::processInput()
{
	player.control();
}
void GameState::update()
{
    oManager.update();
    oManager.interact();
}
void GameState::render(sf::RenderTarget& target, sf::Time frameTime)
{
    target.clear(sf::Color(200, 100, 50));
    oManager.render(target, frameTime);
}
int GameState::gameLoop()
{
	sf::Time accumulator = sf::seconds(0.f);
    sf::Time currentTime = sf::seconds(0.f);
    sf::Clock clock;
    while (window.isOpen() && !isPaused)
    {
        sf::Time newTime = clock.getElapsedTime();
        sf::Time frameTime = newTime - currentTime;
        //printf("FPS: %lf \n", 1 / frameTime.asSeconds());
        if (frameTime >= sf::seconds(0.25f))
            frameTime = sf::seconds(0.25f);
        currentTime = newTime;
        accumulator += frameTime;
        sf::Event event;
        processInput();
        while (window.pollEvent(event)) {
            switch (event.type) {
            case sf::Event::Closed:
                window.close();
                return CLOSED_STATE;
                break;
            default:
                break;
            }
        }
        while (accumulator >= deltaTime) {
            accumulator -= deltaTime;
            update();
        }
        render(window, frameTime);   
        window.display();
    }
    return nextStateIndex;
}

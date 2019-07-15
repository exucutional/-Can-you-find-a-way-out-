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
    lua.open_libraries(sol::lib::base, sol::lib::math);
    lua.new_usertype<AssetManager>("AssetManager", sol::constructors<AssetManager()>(),
        "createTexture", &AssetManager::createTexture<>,
        "createAnimation", &AssetManager::createAnimation<>);
    lua.new_usertype<ObjectManager>("ObjectManager", sol::constructors<ObjectManager()>(),
        "createDynamicGameObject", &ObjectManager::create<DynamicGameObject>);
    lua.new_usertype<Animation>("Animation", sol::constructors<Animation()>(),
        "setSpriteSheet", sol::overload(
            sol::resolve<void(const sf::Texture*)>(&Animation::setSpriteSheet),
            sol::resolve<void(std::shared_ptr<const sf::Texture>)>(&Animation::setSpriteSheet)),
        "addFrame", &Animation::addFrame);
    lua.new_usertype<sf::Texture>("Texture", sol::constructors<sf::Texture(), sf::Texture(const sf::Texture&)>(),
        "loadFromFile", &sf::Texture::loadFromFile,
        "create", &sf::Texture::create);    
    lua.new_usertype<sf::IntRect>("IntRect", sol::constructors<sf::IntRect(), sf::IntRect(int, int, int, int)>());
    lua.new_usertype<GameObject>("GameObject", sol::constructors<GameObject()>(),
        "addAnimation", &GameObject::addAnimation,
        "setAnimation", &GameObject::setAnimation,
        "getAnimation", &GameObject::getAnimation,
        "setPosition", sol::overload(
            sol::resolve<void(float, float)>(&GameObject::setPosition),
            sol::resolve<void(const sf::Vector2f&)>(&GameObject::setPosition)));
    lua.new_usertype<DynamicGameObject>("DynamicGameObject", sol::constructors<DynamicGameObject()>(),
        sol::base_classes, sol::bases<GameObject>());
    lua.new_usertype<Player>("Player", sol::constructors<Player()>(),
        "setObject", sol::overload(
            sol::resolve<void(DynamicGameObject*)>(&Player::setObject),
            sol::resolve<void(std::shared_ptr<DynamicGameObject>)>(&Player::setObject)));
    lua["asManager"] = std::ref(asManager); 
    lua["oManager"] = std::ref(oManager);
    lua["player"] = std::ref(player);
    lua["aDown"] = aDown;
    lua["aLeft"] = aLeft;
    lua["aRight"] = aRight;
    lua["aUp"] = aUp;
    lua.script_file("scripts/gamestate_init.lua");
    /*
    auto texture = asManager.createTexture("mainTexture");
    if (!texture->loadFromFile("texture/animationtest.png"))
    {
        fprintf(stderr, "Loading texture error\n");     
        return;
    }
    auto walkingAnimationDown = asManager.createAnimation("walkingAnimationDown");
    walkingAnimationDown->setSpriteSheet(texture);
    walkingAnimationDown->addFrame(sf::IntRect(32, 0, 32, 32));
    walkingAnimationDown->addFrame(sf::IntRect(64, 0, 32, 32));
    walkingAnimationDown->addFrame(sf::IntRect(32, 0, 32, 32));
    walkingAnimationDown->addFrame(sf::IntRect( 0, 0, 32, 32));
    auto walkingAnimationLeft = asManager.createAnimation("walkingAnimationLeft");
    walkingAnimationLeft->setSpriteSheet(texture);
    walkingAnimationLeft->addFrame(sf::IntRect(32, 32, 32, 32));
    walkingAnimationLeft->addFrame(sf::IntRect(64, 32, 32, 32));
    walkingAnimationLeft->addFrame(sf::IntRect(32, 32, 32, 32));
    walkingAnimationLeft->addFrame(sf::IntRect( 0, 32, 32, 32));
    auto walkingAnimationRight = asManager.createAnimation("walkingAnimationRight");
    walkingAnimationRight->setSpriteSheet(texture);
    walkingAnimationRight->addFrame(sf::IntRect(32, 64, 32, 32));
    walkingAnimationRight->addFrame(sf::IntRect(64, 64, 32, 32));
    walkingAnimationRight->addFrame(sf::IntRect(32, 64, 32, 32));
    walkingAnimationRight->addFrame(sf::IntRect( 0, 64, 32, 32));
    auto walkingAnimationUp = asManager.createAnimation("walkingAnimationUp");
    walkingAnimationUp->setSpriteSheet(texture);
    walkingAnimationUp->addFrame(sf::IntRect(32, 96, 32, 32));
    walkingAnimationUp->addFrame(sf::IntRect(64, 96, 32, 32));
    walkingAnimationUp->addFrame(sf::IntRect(32, 96, 32, 32));
    walkingAnimationUp->addFrame(sf::IntRect( 0, 96, 32, 32));
    
    auto mainObj = oManager.create<DynamicGameObject>();
    player.setObject(mainObj);
    mainObj->addAnimation(walkingAnimationDown, aDown);
    mainObj->addAnimation(walkingAnimationLeft, aLeft);
    mainObj->addAnimation(walkingAnimationUp, aUp);
    mainObj->addAnimation(walkingAnimationRight, aRight);
    mainObj->setVelocity({0.f, 0.f});
    mainObj->setPosition(sf::Vector2f({0, 0}));
    mainObj->setAnimation(mainObj->getAnimation(aDown));
    */
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
            while (accumulator >= deltaTime) {
                accumulator -= deltaTime;
                switch (event.type) {
                case sf::Event::Closed:
                    window.close();
                    return CLOSED_STATE;
                    break;
                default:
                    break;
                }
                update();
            }
        }
        render(window, frameTime);   
        window.display();
    }
    return nextStateIndex;
}

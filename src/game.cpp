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
    for (auto obj: objVec) {
        if (obj)
            delete obj;
    }
    objVec.clear();
}
void ObjectManager::addObject(GameObject* newObj)
{
    objVec.push_back(newObj);
}
const GameObject* ObjectManager::getObject(std::size_t num) const
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
/*
void App::render(sf::RenderTarget& target, sf::Time frameTime)
{
    target.clear(sf::Color(200, 100, 50));
    oManager.render(target, frameTime);
}
*/
/*
int App::init()
{
    auto mainObj = new DynamicGameObject;
    player.setObject(mainObj);
    auto texture = new sf::Texture;
    if (!texture->loadFromFile("texture/animationtest.png"))
    {
        fprintf(stderr, "Loading texture error\n");     
        return EXIT_FAILURE;
    }
    auto walkingAnimationDown = new Animation;
    walkingAnimationDown->setSpriteSheet(*texture);
    walkingAnimationDown->addFrame(sf::IntRect(32, 0, 32, 32));
    walkingAnimationDown->addFrame(sf::IntRect(64, 0, 32, 32));
    walkingAnimationDown->addFrame(sf::IntRect(32, 0, 32, 32));
    walkingAnimationDown->addFrame(sf::IntRect( 0, 0, 32, 32));
    auto walkingAnimationLeft = new Animation;
    walkingAnimationLeft->setSpriteSheet(*texture);
    walkingAnimationLeft->addFrame(sf::IntRect(32, 32, 32, 32));
    walkingAnimationLeft->addFrame(sf::IntRect(64, 32, 32, 32));
    walkingAnimationLeft->addFrame(sf::IntRect(32, 32, 32, 32));
    walkingAnimationLeft->addFrame(sf::IntRect( 0, 32, 32, 32));
    auto walkingAnimationRight = new Animation;
    walkingAnimationRight->setSpriteSheet(*texture);
    walkingAnimationRight->addFrame(sf::IntRect(32, 64, 32, 32));
    walkingAnimationRight->addFrame(sf::IntRect(64, 64, 32, 32));
    walkingAnimationRight->addFrame(sf::IntRect(32, 64, 32, 32));
    walkingAnimationRight->addFrame(sf::IntRect( 0, 64, 32, 32));
    auto walkingAnimationUp = new Animation;
    walkingAnimationUp->setSpriteSheet(*texture);
    walkingAnimationUp->addFrame(sf::IntRect(32, 96, 32, 32));
    walkingAnimationUp->addFrame(sf::IntRect(64, 96, 32, 32));
    walkingAnimationUp->addFrame(sf::IntRect(32, 96, 32, 32));
    walkingAnimationUp->addFrame(sf::IntRect( 0, 96, 32, 32));
    mainObj->addAnimation(walkingAnimationDown, aDown);
    mainObj->addAnimation(walkingAnimationLeft, aLeft);
    mainObj->addAnimation(walkingAnimationUp, aUp);
    mainObj->addAnimation(walkingAnimationRight, aRight);
    mainObj->setVelocity({0.f, 0.f});
    mainObj->setPosition(sf::Vector2f({0, 0}));
    mainObj->setAnimation(mainObj->getAnimation(aDown));
    oManager.addObject(mainObj);
    return EXIT_SUCCESS;
}
*/
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
    //gameLoop();
    return EXIT_SUCCESS;
}
/*
int App::gameLoop()
{
    sf::Time accumulator = sf::seconds(0.f);
    sf::Time currentTime = sf::seconds(0.f);
    sf::Clock clock;
    while (window.isOpen())
    {
        sf::Time newTime = clock.getElapsedTime();
        sf::Time frameTime = newTime - currentTime;
        //printf("FPS: %lf \n", 1 / frameTime.asSeconds());
        if (frameTime >= sf::seconds(0.25f))
            frameTime = sf::seconds(0.25f);
        currentTime = newTime;
        accumulator += frameTime;
        sf::Event event;
        while (window.pollEvent(event)) {   
            while (accumulator >= deltaTime) {
                accumulator -= deltaTime;
                switch (event.type) {
                case sf::Event::Closed:
                    window.close();
                    break;
                default:
                    break;
                }
                gameStep();
            }
        }
        player.control();
        render(window, frameTime);   
        window.display();
    }
    return EXIT_SUCCESS;
}
*/
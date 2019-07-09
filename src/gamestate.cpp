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
	auto mainObj = new DynamicGameObject;
    player.setObject(mainObj);
    auto texture = asManager.create<sf::Texture>("mainTexture");
    if (!texture->loadFromFile("texture/animationtest.png"))
    {
        fprintf(stderr, "Loading texture error\n");     
        return;
    }
    auto walkingAnimationDown = asManager.create<Animation>("walkingAnimationDown");
    walkingAnimationDown->setSpriteSheet(texture);
    walkingAnimationDown->addFrame(sf::IntRect(32, 0, 32, 32));
    walkingAnimationDown->addFrame(sf::IntRect(64, 0, 32, 32));
    walkingAnimationDown->addFrame(sf::IntRect(32, 0, 32, 32));
    walkingAnimationDown->addFrame(sf::IntRect( 0, 0, 32, 32));
    auto walkingAnimationLeft = asManager.create<Animation>("walkingAnimationLeft");
    walkingAnimationLeft->setSpriteSheet(texture);
    walkingAnimationLeft->addFrame(sf::IntRect(32, 32, 32, 32));
    walkingAnimationLeft->addFrame(sf::IntRect(64, 32, 32, 32));
    walkingAnimationLeft->addFrame(sf::IntRect(32, 32, 32, 32));
    walkingAnimationLeft->addFrame(sf::IntRect( 0, 32, 32, 32));
    auto walkingAnimationRight = asManager.create<Animation>("walkingAnimationRight");
    walkingAnimationRight->setSpriteSheet(texture);
    walkingAnimationRight->addFrame(sf::IntRect(32, 64, 32, 32));
    walkingAnimationRight->addFrame(sf::IntRect(64, 64, 32, 32));
    walkingAnimationRight->addFrame(sf::IntRect(32, 64, 32, 32));
    walkingAnimationRight->addFrame(sf::IntRect( 0, 64, 32, 32));
    auto walkingAnimationUp = asManager.create<Animation>("walkingAnimationUp");
    walkingAnimationUp->setSpriteSheet(texture);
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

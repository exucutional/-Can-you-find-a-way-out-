#include "animation.hpp"
Animation::Animation(): 
texture_ptr(nullptr) 
{
	__DEBUG_EXEC(std::cout << "Animation()\n");
}
Animation::Animation(const Animation& animation)
{
	__DEBUG_EXEC(std::cout << "Animation(copy)");
	texture_ptr = animation.texture_ptr;
	Frames_ = animation.Frames_;
}
Animation::Animation(Animation&& animation)
{
	__DEBUG_EXEC(std::cout << "Animation(move)");
	texture_ptr.swap(animation.texture_ptr);
	Frames_.swap(animation.Frames_);
}
Animation& Animation::operator=(const Animation& animation)
{
	texture_ptr = animation.texture_ptr;
	Frames_ = animation.Frames_;
	return *this;
}
Animation& Animation::operator=(Animation&& animation)
{
	texture_ptr.swap(animation.texture_ptr);
	Frames_.swap(animation.Frames_);
	return *this;
}
Animation::~Animation() 
{
	__DEBUG_EXEC(std::cout << "~Animation()\n");
}
void Animation::addFrame(sf::IntRect rect)
{
	Frames_.push_back(rect);
}
void Animation::setSpriteSheet(const sf::Texture* texture_ptr_)
{
	texture_ptr = std::shared_ptr<const sf::Texture>(texture_ptr_);
}
void Animation::setSpriteSheet(std::shared_ptr<const sf::Texture> texture_ptr_)
{
	texture_ptr = texture_ptr_;
}
const sf::Texture* Animation::getSpriteSheet() const
{
	return texture_ptr.get();
}
std::size_t Animation::getSize() const
{
	return Frames_.size();
}
const sf::IntRect& Animation::getFrame(std::size_t num) const
{
	return Frames_[num];
}
AnimationManager::AnimationManager(sf::Time frameTime, bool Pause, bool Loop):
	animation_(nullptr),
	frameTime_(frameTime),
	currentFrame_(0),
	isPaused_(Pause),
	isLooped_(Loop)
{
	__DEBUG_EXEC(std::cout << "AnimationManager(sf::Time, bool, bool)\n");
}
AnimationManager::~AnimationManager()
{
	__DEBUG_EXEC(std::cout << "~AnimationManager()\n");
}
void AnimationManager::setAnimation(const Animation& animation)
{
	animation_ = &animation;
	currentFrame_ = 0;
	texture_ = animation_->getSpriteSheet();
	setFrame(currentFrame_);
}
const Animation* AnimationManager::getAnimation() const
{
	return animation_;
}
void AnimationManager::play()
{
	isPaused_ = false;
}
void AnimationManager::play(const Animation& animation)
{
	if (animation_ != &animation)
		setAnimation(animation);
	play();
}
void AnimationManager::pause()
{
	isPaused_ = true;
}
void AnimationManager::stop()
{
	isPaused_ = true;
	currentFrame_ = 0;
	setFrame(currentFrame_, true);
}
void AnimationManager::setFrameTime(sf::Time time)
{
	frameTime_ = time;
}
sf::FloatRect AnimationManager::getLocalBounds() const 
{
	sf::IntRect rect = animation_->getFrame(currentFrame_);
	float width = static_cast<float>(std::abs(rect.width));
	float height = static_cast<float>(std::abs(rect.height));
	return sf::FloatRect(0.f, 0.f, width, height);
}
sf::FloatRect AnimationManager::getGlobalBounds() const
{
	return getTransform().transformRect(getLocalBounds());
}
void AnimationManager::setLooped(bool Looped)
{
	isLooped_ = Looped;
}
void AnimationManager::setPaused(bool Paused)
{
	isPaused_ = Paused;
}
bool AnimationManager::isLooped() const 
{
	return isLooped_;
}
bool AnimationManager::isPaused() const
{
	return isPaused_;
}
void AnimationManager::setFrame(std::size_t newFrame, bool resetTime)
{
	if (animation_) {
		sf::IntRect rect = animation_->getFrame(newFrame);
		float rectHeight = static_cast<float>(rect.height);
		float rectWidth = static_cast<float>(rect.width);
		vertices[0].position = sf::Vector2f(0.f, 0.f);
		vertices[1].position = sf::Vector2f(0.f, rectHeight);
		vertices[2].position = sf::Vector2f(rectWidth, rectHeight);
		vertices[3].position = sf::Vector2f(rectWidth, 0.f);
		float left = rect.left + 0.0001f;
		float right = left + rectWidth;
		float top = static_cast<float>(rect.top);
		float bottom = top + rectHeight;
		vertices[0].texCoords = sf::Vector2f(left, top);
		vertices[1].texCoords = sf::Vector2f(left, bottom);
		vertices[2].texCoords = sf::Vector2f(right, bottom);
		vertices[3].texCoords = sf::Vector2f(right, top);
	}
	if (resetTime) 
		currentTime_ = sf::Time::Zero;
}
void AnimationManager::update(sf::Time deltaTime)
{
	if (!isPaused_ && animation_) {
		currentTime_ += deltaTime;
		if (currentTime_ >= frameTime_) {
			currentTime_ = sf::microseconds(currentTime_.asMicroseconds() % frameTime_.asMicroseconds());
			if (currentFrame_ + 1 < animation_->getSize())
				currentFrame_++;
			else {
				currentFrame_ = 0;
				if (isLooped_) 
					isPaused_ = true;
			}
			setFrame(currentFrame_, false);
		}
	}
}
void AnimationManager::draw(sf::RenderTarget& target, sf::RenderStates states) const 
{
	if (animation_ && texture_) {
		states.transform *= getTransform();
		states.texture = texture_;
		target.draw(vertices, 4, sf::Quads, states);
	}
}
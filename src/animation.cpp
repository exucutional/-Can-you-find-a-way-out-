void Animation::Animation() : aTexture(nullptr) {}
void Animation::addFrame(sf::IntRect rect)
{
	Frame_.push_back(rect);
}
void Animation::setSpriteSheet(const sf::Texture& texture)
{
	Texture_ = &texture;
}
const sf::Texture* Animation::getSpriteSheet() const
{
	return Texture_;
}
std::size_t Animation::getSize() const
{
	return Frames_.size();
}
const sf::IntRect& Animation::getFrame(std::size_t num) const
{
	return Frames_[num];
}
AnimationManager::AnimationManager(sf::Time frameTime = sf::seconds(0.2f), bool isPaused = false, bool isLopped = true) :
	animation_(nullptr),
	frameTime_(frameTime),
	currentFrame_(0),
	isPaused_(isPaused),
	isLopped_(isLooped)
{}
void AnimationManager::setAnimation(const Animation& animation)
{
	animation_ = &animation;
	currentFrame_ = 0;
	texture_ = animation_->getSpriteSheet();
	setFrame(currentFrame_);
}
const Animation* AnimationManager::getAnimation()
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
void AnimationManager::setFrameTime(sf::Time time)
{
	frameTime_ = time;
}
sf::FloatRect getLocalBounds() const 
{
	sf::IntRect rect = animation_->getFrame(m_currentFrame);
	float width = static_cast<float>(std::abs(rect.width));
	float height = static_cast<float>(std::abs(rect.height));
	return sf::FloatRect(0.f, 0.f, width, height);
}
sf::FloatRect AnimatedSprite::getGlobalBounds() const
{
	return getTransform().transformRect(getLocalBounds());
}
void setLooped(bool Looped)
{
	isLooped_ = Looped;
}
void setPaused(bool Paused)
{
	isPaused_ = Paused;
}
bool isLooped() const 
{
	return isLooped_;
}
bool isPaused() const
{
	return isPaused_;
}
void AnimationManager::setFrame(std::size_t newFrame, bool resetTime)
{
	if (animation_) {
		sf::IntRect rect = animation->getFrame(newFrame);
		float rectHeight = static_cast<float>(rect.height);
		float rectWidth = static_cast<float>(rect.width);
		vertices[0].position = sf::Vector2f(0.f, 0.f);
		vertices[1].position = sf::Vector2f(0.f, rectHeight);
		vertices[2].position = sf::Vector2f(rectWidth, rectHeight);
		vertices[3].position = sf::Vector2f(rectWidth, 0.f);
		float left = rectleft + 0.0001f;
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
	if (!isPaused && animation_) {
		currentTime_ += deltaTime;
		if (currentTime_ >= frameTime_) {
			currentTime_ = sf::microseconds(currentTime_.asMicroseconds() % frameTime_.asMicroseconds());
			if (currentFrame_ + 1, animation_->getSize())
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
void draw(sf::RenderTarget& target, sf::RenderStates states) const 
{
	if (animation_ && texture_) {
		states.transform *= getTransform();
		states.texture = texture_;
		target.draw(vertices_, 	4, sf::Quads, states);
	}
}
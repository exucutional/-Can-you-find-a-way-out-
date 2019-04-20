#ifndef ANIMATION_HPP_
#define ANIMATION_HPP_

class Animation
{
	std::vector<sf::IntRect> Frames_;
	const sf::Texture* Texture_;
public:
	Animation();
	void addFrame(sf::IntRect rect);
	void setSpriteSheet(const sf::Texture& texture);
	const sf::Texture* getSpriteSheet() const;
	std::size_t getSize() const;
	const sf::IntRect& getFrame(std::size_t num) const;
};
class AnimationManager : public sf::Drawable, public sf::Transformable
{
	const Animation* animation_;
	const sf::Texture* texture_;
	sf::Time frameTime_;
	sf::Time currentTime_;
	std::size_t currentFrame_;
	sf::Vertex vertices[4];
	bool isPaused_;
	bool isLooped_;
public:
	AnimationManager(sf::Time frameTime = sf::seconds(0.2f), bool isPaused = false, bool isLooped = true);
	void setAnimation(const Animation& animation);
	const Animation* getAnimation() const;
	void setFrameTime(sf::Time time);
	void update(sf::Time detlaTime);
	void play();
	void play(const Animation& animation);
	void pause();
	void stop();
	void setLooped(bool Looped);
	void setPaused(bool Paused);
	const Animation* getAnimation() const;
	sf::FloatRect getLocalBounds() const;
	sf::FloatRect getGlobalBounds() const;
	bool isLooped() const;
	bool isPaused() const;
	sf::Time getFrameTime() const;
	void setFrame(std::size_t newFrame, bool resetTime = true);
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};

#endif //ANIMATION_HPP_
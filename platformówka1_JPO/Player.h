#pragma once

enum PLAYER_ANIMATION_STATES { IDLE = 0, M_LEFT, M_RIGHT, JUMPING, FALLING, ATAC_1 };

class Player
{
private:
	sf::Sprite sprite;
	sf::Texture textureSheet;
	sf::Clock animationTimer;
	sf::Clock deltaClock;
	sf::Time dt;

	//Animation
	short animState;
	sf::IntRect currentFrame;
	bool animationSwitch;

	//Physic
	sf::Vector2f velocity;
	float velocityXMax;
	float velocityXMin;
	float gravity;
	float velocityMaxY;
	float jumpHeight;
	bool faceRight = true;

	//Core
	void initVariables();
	void initTexture();
	void initSprite();
	void initAnimations();
	void initPhysics();

public:

	Player();
	virtual ~Player();

	//Global variables
	bool canJump;

	//Accessors
	const bool& getAnimSwitch();
	const sf::Vector2f getPosition() const;
	const sf::FloatRect getGlobalBounds() const;

	//Modifiers
	void setPosition(const float x, const float y);

	//Functions
	void resetAnimationTimer();
	void Move(float dx, float dy);
	void updatePhysic();
	void updateMovement();
	void updateAnimations();
	void update();
	void render(sf::RenderTarget& target);
};

#include "stdafx.h"
#include "Player.h"

void Player::initVariables()
{
	this->animState = IDLE;
}

void Player::initTexture()
{
	if (!this->textureSheet.loadFromFile("Textures/Player/Punk_sheet.png"))
	{
		std::cout << "ERROR::PLAYER::Could not load the player sheet!" << "\n";
	}
}

void Player::initSprite()
{
	this->sprite.setTexture(this->textureSheet);
	this->currentFrame = sf::IntRect(0, 0, 48, 48);

	this->sprite.setTextureRect(this->currentFrame);
	this->sprite.setScale(3.0f, 3.0f);
}

void Player::initAnimations()
{
	this->animationTimer.restart();
	this->animationSwitch = true;
}

void Player::initPhysics()
{
	this->velocityXMax = 10.f;
	this->velocityXMin = 1.f;
	this->gravity = 0.91f;
	this->velocityMaxY = 100.0f;

	this->canJump = true;
	this->jumpHeight = 80.f;
}

Player::Player()
{
	this->initVariables();
	this->initTexture();
	this->initSprite();
	this->initAnimations();
	this->initPhysics();
}

Player::~Player()
{
}

const bool& Player::getAnimSwitch()
{
	bool anim_switch = this->animationSwitch;

	if (this->animationSwitch)
		this->animationSwitch = false;

	return anim_switch;
}

const sf::Vector2f Player::getPosition() const
{
	return this->sprite.getPosition();
}

const sf::FloatRect Player::getGlobalBounds() const
{
	return this->sprite.getGlobalBounds();
}

void Player::setPosition(const float x, const float y)
{
	this->sprite.setPosition(x, y);
}

void Player::resetAnimationTimer()
{
	this->animationTimer.restart();
	this->animationSwitch = true;
}

void Player::Move(float dx = 1.0f, float dy = 1.0f)
{
	sprite.move(dx, dy);
}

void Player::updatePhysic()
{
	//Gravity
	this->velocity.y += 1.2 * this->gravity;
	//Limit gravity
	if (std::abs(this->velocity.y) > this->velocityMaxY)
	{
		this->velocity.y = this->velocityMaxY * ((this->velocity.y < 0.f) ? -1.f : 1.f);
	}

	//Deceleration
	this->velocity *= 0.8f;

	this->sprite.move(this->velocity);
}

void Player::updateMovement()
{
	this->animState = IDLE;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A)) //Left
	{
		this->canJump = true;
		this->velocity.x = -4.2f;
		this->animState = M_LEFT;
		this->faceRight = false;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)) //Right
	{
		this->canJump = true;
		this->velocity.x = 4.2f;
		this->animState = M_RIGHT;
		this->faceRight = true;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W) && canJump) //JUMPING
	{
		this->canJump = false;
		this->velocity.y = -sqrt(4.0f * 9.81 * jumpHeight);
		if (this->faceRight == true)
			this->velocity.x = sqrt(2.f * 9.81 * jumpHeight);
		else
			this->velocity.x = -sqrt(2.f * 9.81 * jumpHeight);
		this->animState = JUMPING;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space)) //Right
	{
		this->velocity.x = 2.2f;
		if (this->faceRight == true)
		{
			this->velocity.x = 2.f;
		}
		else
		{
			this->velocity.x = -2.f;
		}
		this->animState = ATAC_1;

	}
	this->Move(velocity.x * dt.asSeconds(), this->velocity.y * dt.asSeconds());
	dt = deltaClock.restart();
}

void Player::updateAnimations()
{
	if (this->animState == IDLE)
	{
		if (this->animationTimer.getElapsedTime().asSeconds() >= 0.25f || this->getAnimSwitch())
		{
			this->currentFrame.top = 336.0f;
			this->currentFrame.left += 48.0f;
			if (this->currentFrame.left >= 144.0f)
				this->currentFrame.left = 0;

			this->animationTimer.restart();
			this->sprite.setTextureRect(this->currentFrame);
		}
	}

	else if (this->animState == M_RIGHT)
	{
		if (this->animationTimer.getElapsedTime().asSeconds() >= 0.15f || this->getAnimSwitch())
		{
			this->currentFrame.top = 480.0f;
			this->currentFrame.left += 48.0f;
			if (this->currentFrame.left >= 240.0f)
				this->currentFrame.left = 0;

			this->animationTimer.restart();
			this->sprite.setTextureRect(this->currentFrame);
		}
		this->sprite.setScale(3.0f, 3.0f);
		this->sprite.setOrigin(0.f, 0.f);
	}

	else if (this->animState == M_LEFT)
	{
		if (this->animationTimer.getElapsedTime().asSeconds() >= 0.15f || this->getAnimSwitch())
		{
			this->currentFrame.top = 480.0f;
			this->currentFrame.left += 48.0f;
			if (this->currentFrame.left >= 240.0f)
				this->currentFrame.left = 0;

			this->animationTimer.restart();
			this->sprite.setTextureRect(this->currentFrame);
		}
		this->sprite.setScale(-3.0f, 3.0f);
		this->sprite.setOrigin(this->sprite.getGlobalBounds().width / 6.f, 0.f);
	}

	else if (this->animState == JUMPING)
	{
		if (this->animationTimer.getElapsedTime().asSeconds() >= 0.25f || this->getAnimSwitch())
		{
			this->currentFrame.top = 384.0f;
			this->currentFrame.left += 48.0f;
			if (this->currentFrame.left >= 144.0f)
				this->currentFrame.left = 0;

			this->animationTimer.restart();
			this->sprite.setTextureRect(this->currentFrame);
		}
	}

	else if (this->animState == ATAC_1)
	{
		if (this->animationTimer.getElapsedTime().asSeconds() >= 0.15f || this->getAnimSwitch())
		{
			this->currentFrame.top = 96.0f;
			this->currentFrame.left += 48.0f;
			if (this->currentFrame.left >= 336.0f)
				this->currentFrame.left = 0;

			this->animationTimer.restart();
			this->sprite.setTextureRect(this->currentFrame);
		}
	}

	else
	{
		this->animationTimer.restart();
	}
}

void Player::update()
{
	this->updateMovement();
	this->updateAnimations();
	this->updatePhysic();
}

void Player::render(sf::RenderTarget& target)
{
	target.draw(this->sprite);
}
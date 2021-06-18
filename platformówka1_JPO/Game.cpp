#include "stdafx.h"
#include "Game.h"

void Game::initWindow()
{
	this->window.create(sf::VideoMode(1200, 720), "Back to the past", sf::Style::Close | sf::Style::Titlebar);
	this->window.setFramerateLimit(100);
}

void Game::initWorld()
{
	if (!this->worldBackgroundTex.loadFromFile("Textures/Map/BackgroundMap.png"))
	{
		std::cout << "ERROR::GAME::Could not load the background sheet!" << "\n";
	}
	this->worldBackground.setTexture(this->worldBackgroundTex);
}

void Game::initTiles()
{
	if (!this->tileTex.loadFromFile("Textures/Map/tile.png"))
	{
		std::cout << "ERROR::GAME::Could not load the tile sheet!" << "\n";
	}
	this->tile.setTexture(this->tileTex);
}

void Game::initPlayer()
{
	this->player = new Player();
}

Game::Game()
{
	this->initWindow();
	this->initWorld();
	this->initPlayer();
}

Game::~Game()
{
	delete this->player;
}

void Game::updatePlayer()
{
	this->player->update();
}

void Game::updateWorld()
{
}

void Game::updateCollision()
{
	if (this->player->getGlobalBounds().left < 0.f)
	{
		this->player->setPosition(0.f, this->player->getGlobalBounds().top);
	}

	//Collision bottom of the screen
	if (this->player->getPosition().y + this->player->getGlobalBounds().height > this->window.getSize().y)
	{
		this->player->setPosition(this->player->getPosition().x, this->window.getSize().y - this->player->getGlobalBounds().height);
		this->player->canJump = true;
	}
}

void Game::update()
{
	//Polling window events
	while (this->window.pollEvent(this->evnt))
	{
		switch (this->evnt.type)
		{
		case sf::Event::Closed:
		{
			this->window.close();
			break;
		}
		case sf::Event::KeyPressed:
		{
			if (this->evnt.key.code == sf::Keyboard::Delete)
				this->window.close();
			break;
		}
		case sf::Event::KeyReleased:
		{
			this->player->resetAnimationTimer();
			break;
		}
		}
	}

	this->updatePlayer();
	this->updateCollision();
	this->updateWorld();
}

void Game::renderPlayer()
{
	this->player->render(this->window);
}

void Game::render()
{
	this->window.clear();
	//Render World
	this->renderTiles();
	this->renderWorld();


	//Render Game & Player
	this->renderPlayer();

	this->window.display();
}

void Game::renderWorld()
{
	this->window.draw(this->worldBackground);
}

void Game::renderTiles()
{
	this->window.draw(this->tile);
}

const sf::RenderWindow& Game::getWindow() const
{
	return this->window;
}

#pragma once
#include "stdafx.h"
#include "Player.h"

class Game
{
private:
	sf::RenderWindow window;
	sf::Event evnt;

	//Background
	sf::Texture worldBackgroundTex;
	sf::Sprite worldBackground;

	//Tiles
	sf::Texture tileTex;
	sf::Sprite tile;

	//Player
	Player* player;

	void initWindow();
	void initWorld();
	void initTiles();
	void initPlayer();

public:
	Game();
	virtual ~Game();

	//Function
	void updatePlayer();
	void updateWorld();
	void updateCollision();
	void update();
	void renderPlayer();
	void render();
	void renderWorld();
	void renderTiles();
	const sf::RenderWindow& getWindow() const;

};



#pragma once
#ifndef GAME_H
#define GAME_H

//trrrr ha-cha!

#include <SFML/Graphics.hpp>


/* ========================================
 * +-+-+-+-+-+-+-+
 * |			 |
 * |Game 	     |
 * +-+-+-+-+-+-+-+
 * ========================================*/

class Game{
public:
	Game();
	void run();

private:
	void processEvents();
	void update();
	void render();

private:
	sf::RenderWindow window;
};

#endif // Game_H	

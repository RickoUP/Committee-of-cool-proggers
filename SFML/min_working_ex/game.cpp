#include "game.h"

Game::Game()
: window(sf::VideoMode({800, 800}), "COOL"){
	
}

void Game::run(){
	while(window.isOpen()){
		processEvents();
		update();
		render();
		
	}
}

void Game::processEvents(){

    while (const std::optional event = window.pollEvent())
    {
        if (event->is<sf::Event::Closed>())
            window.close();
    }
}

void Game::update(){
}

void Game::render(){
	window.clear();
	window.display();
}

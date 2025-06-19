#include "game.h"

Game::Game()
: window(sf::VideoMode({800, 800}), "COOL"){
	
}

void Game::run(){
	
//look at the rabbit!

	ResourceHolder<sf::Texture, Textures::ID> texture_holder;
	texture_holder.load(Textures::Rabbit, "Rabbit.png");
	sf::Sprite rabbit(texture_holder.get(Textures::Rabbit));	;

	window.draw(rabbit);
	window.display();	

	while(window.isOpen()){
		processEvents();
//		update();
//		render();
		
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

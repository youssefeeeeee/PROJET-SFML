
#include "Game.h"
#include <iostream>
void Game::initwindow() {
	window.create(sf::VideoMode(800, 600), "course de voiture");
}


Game::Game() {
	this->initwindow();
	this->v.loadfromtxt("./assets/voiture.png",this->window);
	if (!this->b.load("./assets/bgr.png")) {
		std::cerr << "Failed to load background!" << std::endl;
	}
	this->b.resizeToWindow(this->window);
	this->b.setScrollSpeed(150.f);
}

void Game::updatedt()
{
	this->dt = this->dtclock.restart().asSeconds();
}

void Game::updSFMLevent() {

	while (this->window.pollEvent(this->ev)) {
		if (this->ev.type == sf::Event::Closed)
			this->window.close();
		v.update(this->dt);
	}

}

void Game::update() {
	this->updSFMLevent();
	v.handleInput();
	v.update(this->dt);
	b.update(this->dt);
}



void Game::render() {
	this->window.clear();
	b.draw(this->window);
	v.draw(this->window);
	this->window.display();
}
void Game::run() {
	while (this->window.isOpen()) {
		this->updatedt();
		this->update();
		this->render();
	}
}
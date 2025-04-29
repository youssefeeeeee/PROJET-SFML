#pragma once
#ifndef GAME_H
#define GAME_H
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>	
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include "voiture.h"
#include "background.h"

class Game
{
	private : 
		//variables
		sf::RenderWindow window;
		sf::Event ev;
		sf::Clock dtclock;
		float dt;
		//initialization
		void initwindow();
		voiture v;
		Back b;
	public : 
		//constructor/destructor
		Game();

		// functions
		void updatedt();
		void updSFMLevent();
		void update();
		void render();
		void run();
		void resizeViews();
};
#endif // !GAME_H

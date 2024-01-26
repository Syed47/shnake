#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>
#include <string>
#include <vector>
#include <iostream>
#include <thread>
#include <chrono>

#include "Shnake.h"


#define K_UP sf::Keyboard::Up
#define K_DOWN sf::Keyboard::Down
#define K_LEFT sf::Keyboard::Left
#define K_RIGHT sf::Keyboard::Right

class game {

    std::vector<std::vector<sf::RectangleShape>> grid;
    sf::RenderWindow window;
    sf::Font arial;
    sf::Text score;

	int _rows, _cols, _cell_size, _score;
	shnake yena;
	cell food;

public:
	game(int rows, int cols, int cell_size);

	void initGUI();
	void update();
	void start();

	void spawn_food();
	void rebound_shnake();
};

#endif


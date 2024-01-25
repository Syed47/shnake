#include "game.h"

game::game(int rows, int cols, int cell_size) : 
	_rows(rows), 
	_cols(cols), 
	_cell_size(cell_size),
	window(sf::VideoMode(600, 600), "Shnake"),
	yena(shnake()) { 
		initGUI();
	}

void game::initGUI() {
    arial.loadFromFile("Arial.ttf");
    score.setPosition(sf::Vector2f(100, 100));
    score.setCharacterSize(24);
    score.setFont(arial);
    score.setStyle(sf::Text::Bold);
    score.setFillColor(sf::Color::White);
    
    for (int i = 0, y = 0; i < _rows; ++i, y += _cell_size) {
        std::vector<sf::RectangleShape> row;
        for (int j = 0, x = 0; j < _cols; ++j, x += _cell_size) {
            sf::RectangleShape cell(sf::Vector2f(_cell_size, _cell_size));
            cell.setPosition(sf::Vector2f(x, y));
	        // cell.setOutlineThickness(2);
	        // cell.setOutlineColor(sf::Color(21, 21, 21));
            row.push_back(cell);
        }
        grid.push_back(row);
    }
    std::cout << "GUI Initialized." << std::endl;
}

void game::update() {
	window.clear();
    score.setString("Score: 0");
	window.draw(score);
	yena.move();
	for (int i = 0, y = 0; i < _rows; ++i, y += _cell_size) {
	    for (int j = 0, x = 0; j < _cols; ++j, x += _cell_size) {
	    	if (i == yena.head().x() && j == yena.head().y()) {
		        grid[i][j].setFillColor(sf::Color::Red);
	    	} else {
	    		grid[i][j].setFillColor(sf::Color::Black);
	    	}
	        window.draw(grid[i][j]);
	    }
	}
	window.display();
}


void game::start() {
    while (window.isOpen()) {
        sf::Event event;

        while (window.pollEvent(event)) {
            if(event.type == sf::Event::Closed) {
                window.close();
            } else if (event.type == sf::Event::KeyPressed) {
			    if (event.key.code == sf::Keyboard::Up) {
			    	yena.change_dir(direction::UP);
			        std::cout << "Up key pressed" << std::endl;
			    } else if (event.key.code == sf::Keyboard::Down) {
			    	yena.change_dir(direction::DOWN);
			        std::cout << "Down key pressed" << std::endl;
			    } else if (event.key.code == sf::Keyboard::Left) {
			    	yena.change_dir(direction::LEFT);
			        std::cout << "Left key pressed" << std::endl;
			    } else if (event.key.code == sf::Keyboard::Right) {
			    	yena.change_dir(direction::RIGHT);
			        std::cout << "Right key pressed" << std::endl;
			    } else {
			        std::cout << "Not assigned yet." << std::endl;
			    }
			}
			
        }
        update();
        std::this_thread::sleep_for(std::chrono::milliseconds(1000 / yena.speed()));
    }
}



#include "game.h"

game::game(int rows, int cols, int cell_size) : 
	_rows(rows), 
	_cols(cols), 
	_cell_size(cell_size),
	window(sf::VideoMode(800, 800), "Shnake"),
	food(cell(0, 0, cell_of::FOOD)),
	yena(shnake()) { 
		initGUI();
		spawn_food();
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
	        cell.setOutlineThickness(2);
	        cell.setOutlineColor(sf::Color(21, 21, 21));
            row.push_back(cell);
        }
        grid.push_back(row);
    }
}

void game::update() {
	window.clear();
    score.setString("Score: 0");
	window.draw(score);
	yena.move();
	rebound_shnake();
	for (int i = 0, y = 0; i < _rows; ++i, y += _cell_size) {
	    for (int j = 0, x = 0; j < _cols; ++j, x += _cell_size) {
	    	if (i == yena.head().x() && j == yena.head().y() && i == food.x() && j == food.y()) {
	    		if (yena.eat()) {
		    		yena.speed_up();
		    		spawn_food();
		    	} else {
		    		window.close();
		    	}
	    	} else if (i == yena.head().x() && j == yena.head().y()) {
		        grid[i][j].setFillColor(sf::Color::Red);
	    	} else if (i == food.x() && j == food.y()) {
		        grid[i][j].setFillColor(sf::Color::Green);
	    	} else {
	    		grid[i][j].setFillColor(sf::Color::Black);
	    	}
	    	for (auto k = yena.tail().begin(); k < yena.tail().end(); ++k) {
	    		if (i == (*k).x() && j == (*k).y()) {
		        	grid[i][j].setFillColor(sf::Color::Red);
	    		} 
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
			    } else if (event.key.code == sf::Keyboard::Down) {
			    	yena.change_dir(direction::DOWN);
			    } else if (event.key.code == sf::Keyboard::Left) {
			    	yena.change_dir(direction::LEFT);
			    } else if (event.key.code == sf::Keyboard::Right) {
			    	yena.change_dir(direction::RIGHT);
			    } else {
			    	std::cout << "Not assigned yet." << std::endl;
			    }
			}
			
        }
        update();
        std::this_thread::sleep_for(std::chrono::milliseconds(1000 / yena.speed()));
    }
}


void game::spawn_food() {
	srand(static_cast<unsigned int>(time(nullptr)));
	int x = rand() % _rows;
	int y = rand() % _cols;
	food = cell(x, y, cell_of::FOOD);
}

void game::rebound_shnake() {
	if (yena.head().x() < 0) {
		yena.head().x(_rows);
	} else if (yena.head().x() > _rows) {
		yena.head().x(0);
	} else if (yena.head().y() < 0) {
		yena.head().y(_cols);
	} else if (yena.head().y() > _cols) {
		yena.head().y(0);
	}
}
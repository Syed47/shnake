#include "game.h"

game::game(int rows, int cols, int cell_size) : 
	_rows(rows), 
	_cols(cols), 
	_cell_size(cell_size),
	_score(0),
	food(cell(0, 0, cell_of::FOOD)),
	yena(shnake()),
	window(sf::VideoMode(rows * cell_size, cols * cell_size + cols), "Shnake") { 
		initGUI();
		spawn_food();
}

void game::initGUI() {
    arial.loadFromFile("Arial.ttf");
    score.setPosition(sf::Vector2f(10, 0));
    score.setCharacterSize(_cols / 1.15);
    score.setFont(arial);
    score.setStyle(sf::Text::Bold);
    score.setFillColor(sf::Color::White);
    
    for (int i = 0, y = _cell_size; i < _rows; ++i, y += _cell_size) {
        std::vector<sf::RectangleShape> row;
        for (int j = 0, x = 0; j < _cols; ++j, x += _cell_size) {
            sf::RectangleShape cell(sf::Vector2f(_cell_size, _cell_size));
            cell.setPosition(sf::Vector2f(x, y));
            row.push_back(cell);
        }
        grid.push_back(row);
    }
}

void game::update() {
	window.clear();
    score.setString("Score: " + std::to_string(_score));
	
	if (yena.knoted()) {
    	score.setString("...Game Over... - Score: " + std::to_string(_score));
	} else {
		yena.move();
		rebound_shnake();
		for (int i = 0, y = 0; i < _rows; ++i, y += _cell_size) {
		    for (int j = 0, x = 0; j < _cols; ++j, x += _cell_size) {
		    	if (i == yena.head().x() && j == yena.head().y() && i == food.x() && j == food.y()) {
		    		yena.eat();
		    		yena.speed_up();
		    		spawn_food();
		    		if (yena.speed() % 5) _score += 3; // bonus score
		    		else _score++; // normal score
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
	}
	window.draw(score);
	window.display();
}


void game::start() {
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if(event.type == sf::Event::Closed) {
                window.close();
            } else if (event.type == sf::Event::KeyPressed) {
            	direction dir = yena.dir();
			    if (event.key.code == K_UP && dir != direction::DOWN) {
			    	yena.change_dir(direction::UP);
			    } else if (event.key.code == K_DOWN && dir != direction::UP) {
			    	yena.change_dir(direction::DOWN);
			    } else if (event.key.code == K_LEFT && dir != direction::RIGHT) {
			    	yena.change_dir(direction::LEFT);
			    } else if (event.key.code == K_RIGHT && dir != direction::LEFT) {
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
		yena.head().x(_rows - 1);
	} else if (yena.head().x() > _rows - 1) {
		yena.head().x(0);
	} else if (yena.head().y() < 0) {
		yena.head().y(_cols - 1);
	} else if (yena.head().y() > _cols - 1) {
		yena.head().y(0);
	}
}
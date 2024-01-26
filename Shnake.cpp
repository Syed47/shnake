#include "Shnake.h"

// CELL

cell::cell(int x, int y, cell_of type) : _x(x), _y(y), _type(type) {}
// cell::cell(cell& other) : _x(other.x()), _y(other.y()), _type(other.type()) {}

void cell::type(cell_of type) { _type = type; }
void cell::x(int value) { _x = value; }
void cell::y(int value) { _y = value; }
void cell::xy(int x, int y) { _x = x; _y = y; }

cell_of cell::type() const { return _type; }
int cell::x() const { return _x; }
int cell::y() const { return _y; }


// SHNAKE

shnake::shnake() : 
    _speed(4), 
    _head(cell(10, 10, cell_of::SHNAKE)), 
    _tail(std::vector<cell>()) {
    _tail.emplace_back(cell(10, 11, cell_of::SHNAKE));
}

bool shnake::move() {
    int dx = 0, dy = 0, tx = _head.x(), ty = _head.y();
    if (_dir == direction::LEFT) {
        dy = -1;
    } else if (_dir == direction::RIGHT) {
        dy = 1;   
    } else if (_dir == direction::UP) {
        dx = -1;
    } else if (_dir == direction::DOWN) {
        dx = 1;
    } else {
        return false;
    }
    
    _head.xy(tx + dx, ty + dy);

    for (auto i = _tail.begin(); i < _tail.end(); ++i) {
        int ttx = (*i).x(); int tty = (*i).y();
        (*i).xy(tx, ty);        
        tx = ttx; ty = tty;
    }
    return true;
}

bool shnake::knoted() {
    for (auto i = _tail.begin(); i < _tail.end(); ++i) {
        if (i->x() == _head.x() && i->y() == _head.y()) {
            return true;
        }
    }
    return false;
}

void shnake::eat() { 
    _tail.emplace_back(cell(_tail[_tail.size() - 1]));
}

void shnake::change_dir(direction dir) { _dir = dir; }
void shnake::speed_up() { _speed += 1; };


int shnake::speed() { return _speed; }


direction shnake::dir() { return _dir; }

cell& shnake::head() { return _head; }

std::vector<cell>& shnake::tail() { return _tail; }


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

shnake::shnake() : _head(cell(20, 20, cell_of::SHNAKE)), _tail(std::vector<cell>()) {}

bool shnake::move(direction dir) {
    int dx = 0, dy = 0, tx = _head.x(), ty = _head.y();
    if (dir == direction::LEFT) {
        dy = -1;
    } else if (dir == direction::RIGHT) {
        dy = 1;   
    } else if (dir == direction::UP) {
        dx = -1;
    } else if (dir == direction::DOWN) {
        dx = 1;
    } else {
        return false;
    }
    
    _head.xy(tx + dx, ty + dy);
    // for (auto i = _tail.begin(); i < _tail.end(); ++i) {
    //     int ttx = (*i).x(); int tty = (*i).y();
    //     (*i).xy(tx, ty);
    //     tx = ttx; ty = tty;
    // }
    return true;
}

void shnake::eat() { 
    cell tail = cell(_tail[_tail.size()-1]);
    _tail.push_back(tail);
}

cell& shnake::head() { return _head; }

std::vector<cell>& shnake::tail() { return _tail; }


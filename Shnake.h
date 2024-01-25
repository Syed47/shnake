#ifndef SHNAKE_H
#define SHNAKE_H

#include <vector>
#include <iostream>

enum direction { 
    LEFT,
    RIGHT,
    UP,
    DOWN
};

enum cell_of {
    EMPTY,
    FOOD,
    SHNAKE
};

class cell {
    int _x, _y;
    cell_of _type;

public:
    cell(int x, int y, cell_of type);
    // cell(cell& other);

    void type(cell_of type);
    void x(int value);
    void y(int value);
    void xy(int x, int y);

    cell_of type() const;
    int x() const;
    int y() const;
};


class shnake {
    cell _head;
    std::vector<cell> _tail;

public:
    shnake();

    bool move(direction dir);
    void eat();
    cell& head();
    std::vector<cell>& tail();
    // bool isAlive() { return false; }
};


#endif
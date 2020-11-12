#ifndef CELL_H
#define CELL_H

#include <stdint.h>


enum Direction {
    UP,
    DOWN, 
    LEFT,
    RIGHT
};


class Cell {
public:
    Cell(int16_t x, int16_t y, char symbol) : x(x), y(y), symbol(symbol) {}
    
    int16_t X() const { return x; }
    int16_t Y() const { return y; }

    void _setPos(int16_t x, int16_t y);

    void move(Direction direction, int16_t units);

    char getC() const { return symbol; }

    void setC(char c) { symbol = c; }

    bool operator==(const Cell& r_Cell);

    bool operator!=(const Cell& r_Cell);
    
private:
    int16_t x; 
    int16_t y;
    char symbol;
};

const Cell NULL_CELL = Cell(-1, -1, '\0');

#endif
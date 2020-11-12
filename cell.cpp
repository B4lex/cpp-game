#include "cell.hpp"


void Cell::move(Direction direction, int16_t units = 1) {
    switch (direction)
    {
        case UP:
            y -= units;
            break;
        case DOWN:
            y += units;
            break;
        case LEFT:
            x -= units;
            break;
        case RIGHT:
            x += units;
            break;
        default:
            break;
    }
}   

bool Cell::operator==(const Cell& r_Cell) {
    return (this->x == r_Cell.x) && (this->y == r_Cell.y) && (this->symbol == r_Cell.symbol); 
}

bool Cell::operator!=(const Cell& r_Cell) {
    return (this->x != r_Cell.x) | (this->y != r_Cell.y) | (this->symbol != r_Cell.symbol);
}

void Cell::_setPos(int16_t x, int16_t y) {
    this->x = x;
    this->y = y;
}

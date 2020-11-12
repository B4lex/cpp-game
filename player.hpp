#ifndef PLAYER_H
#define PLAYER_H

#include "cell.hpp"


#define PLAYER_ON_GROUND 0
#define PLAYER_ON_AIR 1


class Player : public Cell {
public:
    typedef Cell super;
    Player(uint8_t x, uint8_t y, uint8_t symbol) : super(x, y, symbol) {}
    double relativePos = 0.;
    
    uint8_t getState() { return state; }
    void setState(uint8_t state) { this->state = state; }
private:
    uint8_t state = PLAYER_ON_GROUND;
};

#endif
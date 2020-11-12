#ifndef ENEMY_H
#define ENEMY_H

#include "cell.hpp"

#define HORIZONTAL 0
#define VERTICAL 1


const double e_Velocity = 0.2;


class Enemy : public Cell {
public:
    typedef Cell super;

    Enemy(uint8_t x, uint8_t y, char symbol, uint8_t damage, uint8_t m_Type) :
    super(x, y, symbol), damage(damage), movementType(m_Type) {
        if (movementType == HORIZONTAL) {
            currDir = RIGHT;
        } else {
            currDir = UP;
        }
    };

    uint8_t getMType() { return movementType; }
    
    void move() {
        relativePos += e_Velocity;
        if (relativePos >= 1) {
            super::move(currDir, 1);
            relativePos = 0;
        }
    }

    Direction currDir;
private:
    uint8_t movementType;
    uint8_t damage;
    double relativePos = 0.;
};

Direction getOppositeDirection(Direction dir);

#endif
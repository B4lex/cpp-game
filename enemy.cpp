#include "enemy.hpp"

Direction getOppositeDirection(Direction dir) {
    switch(dir) {
        case UP:
            return DOWN;
            break;
        case DOWN:
            return UP;
            break;
        case LEFT:
            return RIGHT;
            break;
        case RIGHT:
            return LEFT;
            break;
        default:
            return UP;
            break;
    }

}
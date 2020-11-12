#ifndef GAMEFIELD_H
#define GAMEFIELD_H

#include <vector>
#include "cell.hpp"
#include "player.hpp"
#include "enemy.hpp"


extern const double G;


class GameField {
public:
    GameField(const char* fieldData);

    void updateFrame();

    // move cell within field
    void movePlayer(Direction dir);

    void jumpPlayer(uint8_t height = 3);

    ~GameField() {
        delete player;
        delete startPoint;
        delete finishPoint;
    }

private:
    bool display = true;
    std::vector<Cell> cells;
    std::vector<Enemy> enemies;
    Cell *startPoint, *finishPoint;                                                                                                                                                                                                                                                  
    Player *player;
    uint8_t max_X;
    uint8_t max_Y;

    void moveEntity(Cell& entity, Direction dir, uint8_t units = 1);

    const Cell& getCellOnField(uint8_t x, uint8_t y);

    bool isEntityCanMove(Cell& entity, Direction dir, uint8_t units);

    void applyPhysicsToPlayer();

    void onFinish();

    void updateAndDrawEnemies();

    bool isPlayerKilledByEnemies();
};

#endif
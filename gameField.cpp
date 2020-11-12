#include <cstring>
#include <ncurses.h>
#include "gameField.hpp"

GameField::GameField(const char* fieldData) {
    uint32_t dataLen = strlen(fieldData);
    cells.reserve(dataLen);
    uint8_t x_occ = 0, y_occ = 0;
    for (uint32_t i = 0; i < dataLen; ++i) {
        if (fieldData[i] != '\n' && fieldData[i] != '\0') {
            switch(fieldData[i]) {
                case 'S':
                    startPoint = new Cell(x_occ++, y_occ, ' ');
                    cells.push_back(*startPoint);
                    break;
                case 'F':
                    finishPoint = new Cell(x_occ++, y_occ, '*');
                    cells.push_back(*finishPoint);
                    break;
                case 'H':
                    enemies.push_back(
                        Enemy(x_occ, y_occ, 'X', 0, HORIZONTAL)
                    );
                    cells.push_back(
                        Cell(x_occ++, y_occ, ' ')
                    );
                    break;
                case 'V':
                    enemies.push_back(
                        Enemy(x_occ, y_occ, 'X', 0, VERTICAL)
                    );
                    cells.push_back(
                        Cell(x_occ++, y_occ, ' ')
                    );
                    break;
                default:
                    cells.push_back(
                        Cell(x_occ++, y_occ, fieldData[i])
                    );
                    break;
            }
        } else {
            x_occ = 0;
            y_occ++;
        }
    }
    player = new Player(startPoint->X(), startPoint->Y(), 254);
    max_X = cells.back().X() - 1;
    max_Y = cells.back().Y() - 1;
}

void GameField::updateFrame() {
    if (display) {
        for (const Cell& cell : cells) {
            mvaddch(cell.Y(), cell.X(), cell.getC());
        }
        applyPhysicsToPlayer();
        updateAndDrawEnemies();
        if (isPlayerKilledByEnemies()) {
            onFinish();
        }
        mvaddch(player->Y(), player->X(), player->getC());
        mvaddch(finishPoint->Y(), finishPoint->X(), finishPoint->getC());
        mvprintw(20, 0, "%d | %d", player->X(), player->Y());
        if (player->X() == finishPoint->X() && player->Y() == finishPoint->Y()) {
            onFinish();
        }
    }
}

void GameField::movePlayer(Direction dir) {
    moveEntity(*player, dir);
}

void GameField::jumpPlayer(uint8_t height) {
    if (player->getState() == PLAYER_ON_GROUND) {
        if (height != 0) {
            moveEntity(*player, UP, 1);
            jumpPlayer(--height);
        }
    }
}

void GameField::onFinish() { 
    player->_setPos(startPoint->X(), startPoint->Y());
}

// -- private --
void GameField::moveEntity(Cell& entity, Direction dir, uint8_t units) {
    if (isEntityCanMove(entity, dir, units)) {
        entity.move(dir, units);
    }
}

void GameField::applyPhysicsToPlayer() {
    if(isEntityCanMove(*player, DOWN, 1)) {
        player->setState(PLAYER_ON_AIR);
        player->relativePos += G;
        if (player->relativePos > 0) {
            moveEntity(*player, DOWN);
            player->relativePos -= 1;
        }
    } else {
        player->setState(PLAYER_ON_GROUND);
    }
}

bool GameField::isEntityCanMove(Cell& entity, Direction dir, uint8_t units) {
    Cell currCell = Cell(entity);
    uint8_t i_posX = currCell.X();
    uint8_t i_posY = currCell.Y();
    for (int i = 1; i <= units; ++i) {
        currCell.move(dir, i);
        Cell affected_cell = getCellOnField(currCell.X(), currCell.Y());
        if (affected_cell != NULL_CELL && affected_cell.getC() != '#') {
            currCell._setPos(i_posX, i_posY);
        } else {
            return false;
        }
    }
    return true;
}

const Cell& GameField::getCellOnField(uint8_t x, uint8_t y) { 
    for (Cell& cell : cells) {
        if (cell.X() == x && cell.Y() == y) {
            return cell;
        }
    }
    return NULL_CELL;
}

void GameField::updateAndDrawEnemies() {
    for (Enemy& enemy : enemies) {
        if (!isEntityCanMove(enemy, enemy.currDir, 1)) {
            enemy.currDir = getOppositeDirection(enemy.currDir);
        }
        enemy.move();
        mvaddch(enemy.Y(), enemy.X(), enemy.getC());
    }
}

bool GameField::isPlayerKilledByEnemies() {
    for (const Enemy& enemy : enemies) {
        if (player->X() == enemy.X() && player->Y() == enemy.Y()) {
            return true;
        }
    }
    return false;
}
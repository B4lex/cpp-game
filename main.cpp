#include <string>
#include <fstream>
#include <sstream>
#include <ncurses.h>
#include <unistd.h>
#include "gameField.hpp"

#define KEY_SPACE 32


const char* buildLevel(const char* filename);
const double G = 0.3;


int main()
{
    initscr();
    keypad(stdscr, true);
    curs_set(0);
    halfdelay(1);
    GameField field = { buildLevel("level") };
    while (true) {
        clear();
        field.updateFrame();
        refresh();
        switch (getch())
        {
            case KEY_LEFT:
                field.movePlayer(LEFT);
                break;
            case KEY_RIGHT:
                field.movePlayer(RIGHT);
                break;
            case KEY_SPACE:
                field.jumpPlayer();
                break;
            default:
                break;
        }
    }
    return 0;
}


char* levelData = nullptr;


const char* buildLevel(const char* filename) {
    if (!levelData) {
        std::ifstream levelFile(filename);
        std::stringstream fileSStream;
        fileSStream << levelFile.rdbuf();
        std::string levelStr = fileSStream.str();
        uint32_t levelDataLength = levelStr.length();
        const char* str_LevelTmpData = levelStr.c_str();
        levelData = new char[levelDataLength + 1];
        uint32_t i;
        for (i = 0; i < levelDataLength; ++i) {
            levelData[i] = str_LevelTmpData[i];
        }
        levelData[i] = '\0';
    };
    return levelData;
}

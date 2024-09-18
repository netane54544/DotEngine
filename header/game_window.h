#pragma once
#include <string>

class Game_Window
{
    int width, height;

    void draw();
    void destroy();

    public:
    Game_Window(std::string, int, int);
    void gameLoop();
    int getWidth();
    int getHeight();
};
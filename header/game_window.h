#pragma once
#include <string>
#include "GLFW/glfw3.h"

class Game_Window
{
    GLFWwindow* window = nullptr;
    int width, height;
    unsigned int refCount = 0;
    static int instances;

    void draw();

    public:
    Game_Window(std::string, int, int, bool);
    void gameLoop();
    void AddRef();
    void Release();
    int getWidth();
    int getHeight();
};
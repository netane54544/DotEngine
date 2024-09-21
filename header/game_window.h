#pragma once
#include <string>
#include <GLFW/glfw3.h>

class Game_Window
{
    static int width, height;
    int refCount; 

    static void draw();

    public:
    static GLFWwindow* window;
    static bool runLoop;

    Game_Window(std::string, int, int, bool);
    void gameLoop();
    static void runInternalLoop();
    int getWidth();
    int getHeight();

    void AddRef() { refCount++; }
    void Release() 
    {
        if (--refCount == 0) {
            delete this;
        }
    }
};
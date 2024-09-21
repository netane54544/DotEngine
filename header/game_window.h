#pragma once
#include <string>
#include <GLFW/glfw3.h>
#include "vector2.h"
#include "vector4.h"

class Game_Window
{
    int refCount; 

    static void draw();

    public:
    static GLFWwindow* window;
    static bool runLoop;

    Game_Window(const std::string, int, int, bool);
    Game_Window(const std::string, Vector2, bool);
    void gameLoop();
    static void runInternalLoop();
    int getWidth();
    int getHeight();
    void setColorRGBA(Vector4);

    void AddRef();
    void Release();

};

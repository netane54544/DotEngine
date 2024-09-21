#include "game_window.h"
#include <iostream>

GLFWwindow* Game_Window::window = nullptr;
bool Game_Window::runLoop = false;

Game_Window::Game_Window(std::string title, int width, int height, bool fullscreen)
{
    this->refCount = 1;
    
    if (window != nullptr)
        throw "Error: you should create one Game_Window object";

    this->window = glfwCreateWindow(width, height, title.c_str(), fullscreen ? glfwGetPrimaryMonitor() : NULL, NULL);

    if (!window) 
    {
        std::cerr << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
    }

    glfwMakeContextCurrent(this->window);
}

void Game_Window::draw()
{

}

void Game_Window::gameLoop() 
{
    if(runLoop)
    {
        std::cerr << "Error: the gameloop function must be called only once" << std::endl;
        return;
    }

    runLoop = true;
}

void Game_Window::runInternalLoop()
{
    int width = 0;
    int height = 0;

    while (!glfwWindowShouldClose(window)) 
    {
        glfwGetFramebufferSize(window, &width, &height);
        const float ratio = width / (float) height;
 
        glViewport(0, 0, width, height);

        // Clear the screen with a specific color (for example, black)
        glClear(GL_COLOR_BUFFER_BIT);

        draw();

        // Swap buffers (double buffering)
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // You dont need the window anymore
    glfwDestroyWindow(window);
}

int Game_Window::getWidth() 
{
    int width, height;
    glfwGetFramebufferSize(window, &width, &height);

    return width;
}

int Game_Window::getHeight() 
{
    int width, height;
    glfwGetFramebufferSize(window, &width, &height);

    return height;
}
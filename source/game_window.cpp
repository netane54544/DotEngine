#include "game_window.h"
#include <iostream>


int Game_Window::instances = 0;

Game_Window::Game_Window(std::string title, int width, int height, bool fullscreen)
{
    this->width = width;
    this->height = height;
    
    this->window = glfwCreateWindow(width, height, title.c_str(), fullscreen ? glfwGetPrimaryMonitor() : NULL, NULL);

    if (!window) 
    {
        std::cerr << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
    }

    instances++;
    glfwMakeContextCurrent(this->window);
}

void Game_Window::AddRef()
{
    refCount++;
}

void Game_Window::Release()
{
    if (--refCount == 0) 
    {
        instances--;
        delete this;
    }
}

void Game_Window::draw()
{

}

void Game_Window::gameLoop() 
{
    if(refCount > 0)
        throw "A window gameloop is allowed to be called only once";

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
    return width;
}

int Game_Window::getHeight() 
{
    return height;
}
#include "game_window.h"

Game_Window::Game_Window(std::string title, int width, int height)
{
    this->width = width;
    this->height = height;
}

void Game_Window::gameLoop() {
    // Implementation here
}

int Game_Window::getWidth() {
    return width;  // or appropriate logic
}

int Game_Window::getHeight() {
    return height;  // or appropriate logic
}
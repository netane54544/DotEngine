#pragma once
#include <angelscript.h>
#include <string>
#include "game_window.h"

// Function to register the Game_Window class and its methods in AngelScript
void RegisterGameWindow(asIScriptEngine* engine);

// Declare the factory function for creating Game_Window instances
Game_Window* GameWindowFactory(const std::string& title, int width, int height);

// Function to register the Print function
void RegisterPrintFunction(asIScriptEngine* engine);

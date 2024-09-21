#include "bindings.h"
#include "scriptstdstring.h"
#include <iostream>

// Factory function for Game_Window class
Game_Window* GameWindowFactory(const std::string& title, int width, int height, bool fullscreen)
{
    return new Game_Window(title, width, height, fullscreen);
}

// Simple print function for AngelScript
void Print(const std::string& message) 
{
    std::cout << message << std::endl;
}

// Function to register the Print function in AngelScript
void RegisterPrintFunction(asIScriptEngine* engine) 
{
    // Register the Print function
    int r = engine->RegisterGlobalFunction("void Print(const string &in)", asFUNCTION(Print), asCALL_CDECL);

    if (r < 0)
        std::cerr << "Failed to register Print function." << std::endl;
}

void RegisterGameWindow(asIScriptEngine* engine) 
{
    int r;

    // Register Game_Window type with reference counting
    r = engine->RegisterObjectType("Game_Window", 0, asOBJ_REF);
    if (r < 0) std::cerr << "Failed to register Game_Window type." << std::endl;

    // Register the factory function for creating Game_Window instances
    r = engine->RegisterObjectBehaviour("Game_Window", asBEHAVE_FACTORY, 
        "Game_Window@ f(const string &in, int, int, bool)", 
        asFUNCTION(GameWindowFactory), asCALL_CDECL);
    if (r < 0) std::cerr << "Failed to register Game_Window factory." << std::endl;

    
    // Register the AddRef and Release behaviors for reference counting
    r = engine->RegisterObjectBehaviour("Game_Window", asBEHAVE_ADDREF, 
        "void f()", asMETHOD(Game_Window, AddRef), asCALL_THISCALL);
    if (r < 0) std::cerr << "Failed to register AddRef." << std::endl;

    r = engine->RegisterObjectBehaviour("Game_Window", asBEHAVE_RELEASE, 
        "void f()", asMETHOD(Game_Window, Release), asCALL_THISCALL);
    if (r < 0) std::cerr << "Failed to register Release." << std::endl;
    

    // Register methods for Game_Window
    r = engine->RegisterObjectMethod("Game_Window", "void gameLoop()", 
        asMETHOD(Game_Window, gameLoop), asCALL_THISCALL);
    if (r < 0) std::cerr << "Failed to register gameLoop() method." << std::endl;

    r = engine->RegisterObjectMethod("Game_Window", "int getWidth()", asMETHOD(Game_Window, getWidth), asCALL_THISCALL);
    if (r < 0) std::cerr << "Failed to register getWidth() method." << std::endl;

    r = engine->RegisterObjectMethod("Game_Window", "int getHeight()", asMETHOD(Game_Window, getHeight), asCALL_THISCALL);
    if (r < 0) std::cerr << "Failed to register getHeight() method." << std::endl;
}

#include "bindings.h"
#include "scriptstdstring.h"
#include "vector2.h"
#include "vector3.h"
#include "vector4.h"
#include <iostream>


Game_Window* GameWindowFactory(const std::string& title, int width, int height, bool fullscreen)
{
    return new Game_Window(title, width, height, fullscreen);
}

Game_Window* GameWindowFactory(const std::string& title, Vector2 dims, bool fullscreen)
{
    return new Game_Window(title, dims, fullscreen);
}

void Print(const std::string& message) 
{
    std::cout << message << std::endl;
}

void Print(const Vector2& vec) 
{
    std::cout << "Vector2(" << vec.x << ", " << vec.y << ")" << std::endl;
}

void Print(const Vector3& vec) 
{
    std::cout << "Vector3(" << vec.x << ", " << vec.y << ", " << vec.z << ")" << std::endl;
}

void Print(const Vector4& vec) 
{
    std::cout << "Vector4(" << vec.x << ", " << vec.y << ", " << vec.z << ", " << vec.h << ")" << std::endl;
}

void ConstructVector2(Vector2* self) 
{
    new(self) Vector2();
}

void ConstructVector2Init(Vector2* self, float x, float y) 
{
    new(self) Vector2(x, y);
}

void ConstructVector3(Vector3* self) 
{
    new(self) Vector3();
}

void ConstructVector3Init(Vector3* self, float x, float y, float z) 
{
    new(self) Vector3(x, y, z);
}

void ConstructVector4(Vector4* self) 
{
    new(self) Vector4();
}

void ConstructVector4Init(Vector4* self, float x, float y, float z, float h) 
{
    new(self) Vector4(x, y, z, h);
}

// Function to register the Print function in AngelScript
void RegisterPrintFunction(asIScriptEngine* engine) 
{
    engine->RegisterGlobalFunction("void Print(const string &in)", asFUNCTION((void (*)(const std::string&))Print), asCALL_CDECL);
    engine->RegisterGlobalFunction("void Print(const Vector2 &in)", asFUNCTION((void (*)(const Vector2&))Print), asCALL_CDECL);
    engine->RegisterGlobalFunction("void Print(const Vector3 &in)", asFUNCTION((void (*)(const Vector3&))Print), asCALL_CDECL);
    engine->RegisterGlobalFunction("void Print(const Vector4 &in)", asFUNCTION((void (*)(const Vector4&))Print), asCALL_CDECL);
}

void RegisterVectors(asIScriptEngine* engine) 
{
    // Register Vector2 type and basic operations
    engine->RegisterObjectType("Vector2", sizeof(Vector2), asOBJ_VALUE | asOBJ_POD | asGetTypeTraits<Vector2>());
    engine->RegisterObjectBehaviour("Vector2", asBEHAVE_CONSTRUCT, "void f()", asFUNCTION(ConstructVector2), asCALL_CDECL_OBJFIRST);
    engine->RegisterObjectBehaviour("Vector2", asBEHAVE_CONSTRUCT, "void f(float, float)", asFUNCTION(ConstructVector2Init), asCALL_CDECL_OBJFIRST);
    
    // Register Vector3 type and basic operations
    engine->RegisterObjectType("Vector3", sizeof(Vector3), asOBJ_VALUE | asOBJ_POD | asGetTypeTraits<Vector3>());
    engine->RegisterObjectBehaviour("Vector3", asBEHAVE_CONSTRUCT, "void f()", asFUNCTION(ConstructVector3), asCALL_CDECL_OBJFIRST);
    engine->RegisterObjectBehaviour("Vector3", asBEHAVE_CONSTRUCT, "void f(float, float, float)", asFUNCTION(ConstructVector3Init), asCALL_CDECL_OBJFIRST);
    
    // Register Vector4 type and basic operations
    engine->RegisterObjectType("Vector4", sizeof(Vector4), asOBJ_VALUE | asOBJ_POD | asGetTypeTraits<Vector4>());
    engine->RegisterObjectBehaviour("Vector4", asBEHAVE_CONSTRUCT, "void f()", asFUNCTION(ConstructVector4), asCALL_CDECL_OBJFIRST);
    engine->RegisterObjectBehaviour("Vector4", asBEHAVE_CONSTRUCT, "void f(float, float, float, float)", asFUNCTION(ConstructVector4Init), asCALL_CDECL_OBJFIRST);
    
    // Register Vector2 methods
    engine->RegisterObjectMethod("Vector2", "Vector2 opAdd(const Vector2 &in)", asMETHOD(Vector2, operator+), asCALL_THISCALL);
    engine->RegisterObjectMethod("Vector2", "Vector3 addDim()", asMETHOD(Vector2, addDim), asCALL_THISCALL);

    // Register Vector3 methods
    engine->RegisterObjectMethod("Vector3", "Vector3 opAdd(const Vector3 &in)", asMETHOD(Vector3, operator+), asCALL_THISCALL);
    engine->RegisterObjectMethod("Vector3", "Vector4 addDim()", asMETHOD(Vector3, addDim), asCALL_THISCALL);
    engine->RegisterObjectMethod("Vector3", "Vector2 removeDim()", asMETHOD(Vector3, removeDim), asCALL_THISCALL);

    // Register Vector4 methods
    engine->RegisterObjectMethod("Vector4", "Vector4 opAdd(const Vector4 &in)", asMETHOD(Vector4, operator+), asCALL_THISCALL);
    engine->RegisterObjectMethod("Vector4", "Vector3 removeDim()", asMETHOD(Vector4, removeDim), asCALL_THISCALL);
}

void RegisterGameWindow(asIScriptEngine* engine) 
{
    int r;

    // Register Game_Window type with reference counting
    r = engine->RegisterObjectType("Game_Window", 0, asOBJ_REF);
    if (r < 0) std::cerr << "Failed to register Game_Window type." << std::endl;
    
    // Register the factory function that takes Vector2 for dimensions
    engine->RegisterObjectBehaviour("Game_Window", asBEHAVE_FACTORY,
        "Game_Window@ f(const string &in, const Vector2 &in, bool)", 
        asFUNCTION((Game_Window*(*)(const std::string&, Vector2, bool))GameWindowFactory), asCALL_CDECL);
    if (r < 0) std::cerr << "Failed to register Game_Window factory." << std::endl;

    // Register the factory function that takes int width and height
    engine->RegisterObjectBehaviour("Game_Window", asBEHAVE_FACTORY,
        "Game_Window@ f(const string &in, int, int, bool)", 
        asFUNCTION((Game_Window*(*)(const std::string&, int, int, bool))GameWindowFactory), asCALL_CDECL);
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

    r = engine->RegisterObjectMethod("Game_Window", "void setColorRGBA(Vector4)", asMETHOD(Game_Window, setColorRGBA), asCALL_THISCALL);
    if (r < 0) std::cerr << "Failed to register getHeight() method." << std::endl;
}

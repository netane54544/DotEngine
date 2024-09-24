#include "bindings.h"
#include "game_window.h"
#include "Objects_H/object.h"
#include "Objects_H/world.h"
#include "scriptarray.h"
#include "scriptstdstring.h"
#include "Math_H/vector2.h"
#include "Math_H/vector3.h"
#include "Math_H/vector4.h"
#include "Math_H/mat3.h"
#include "Math_H/mat4.h"
#include <iostream>


Game_Window* GameWindowFactory(const std::string& title, int width, int height, bool fullscreen)
{
    return new Game_Window(title, width, height, fullscreen);
}

Game_Window* GameWindowFactory(const std::string& title, Vector2 dims, bool fullscreen)
{
    return new Game_Window(title, dims, fullscreen);
}

World* WorldFactory() 
{
    return new World();
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

void Print(const Mat3& mat)
{
    for (int row = 0; row < 3; row++) 
    {
        for (int col = 0; col < 3; col++) 
        {
            std::cout << mat.elements[row * 3 + col] << " ";
        }

        std::cout << std::endl;
    }
}

void Print(const Mat4& mat)
{
    for (int row = 0; row < 4; row++) 
    {
        for (int col = 0; col < 4; col++) 
        {
            std::cout << mat.elements[row * 4 + col] << " ";
        }

        std::cout << std::endl;
    }
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

static void ConstructMat3(void* memory) 
{
    new(memory) Mat3();
}

static void ConstructMat3WithDiagonal(void* memory, float diagonal) 
{
    new(memory) Mat3(diagonal);
}

static void ConstructMat4(void* memory) 
{
    new(memory) Mat4();
}

static void ConstructMat4WithDiagonal(void* memory, float diagonal) 
{
    new(memory) Mat4(diagonal);
}

// Function to register the Print function in AngelScript
void RegisterPrintFunction(asIScriptEngine* engine) 
{
    engine->RegisterGlobalFunction("void Print(const string &in)", asFUNCTION((void (*)(const std::string&))Print), asCALL_CDECL);
    engine->RegisterGlobalFunction("void Print(const Vector2 &in)", asFUNCTION((void (*)(const Vector2&))Print), asCALL_CDECL);
    engine->RegisterGlobalFunction("void Print(const Vector3 &in)", asFUNCTION((void (*)(const Vector3&))Print), asCALL_CDECL);
    engine->RegisterGlobalFunction("void Print(const Vector4 &in)", asFUNCTION((void (*)(const Vector4&))Print), asCALL_CDECL);
    engine->RegisterGlobalFunction("void Print(const Mat3 &in)", asFUNCTION((void (*)(const Mat3&))Print), asCALL_CDECL);
    engine->RegisterGlobalFunction("void Print(const Mat4 &in)", asFUNCTION((void (*)(const Mat4&))Print), asCALL_CDECL);
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

void RegisterMatrices(asIScriptEngine* engine) 
{
    // Register Mat3
    engine->RegisterObjectType("Mat3", sizeof(Mat3), asOBJ_VALUE | asOBJ_POD | asGetTypeTraits<Mat3>());
    engine->RegisterObjectBehaviour("Mat3", asBEHAVE_CONSTRUCT, "void f()", asFUNCTION(ConstructMat3), asCALL_CDECL_OBJFIRST);
    engine->RegisterObjectBehaviour("Mat3", asBEHAVE_CONSTRUCT, "void f(float)", asFUNCTION(ConstructMat3WithDiagonal), asCALL_CDECL_OBJFIRST);

    // Register Mat3 methods (use wrappers instead of overloaded operators)
    engine->RegisterObjectMethod("Mat3", "Mat3 multiplyMat3(const Mat3 &in)", asMETHOD(Mat3, multiplyMat3), asCALL_THISCALL);
    engine->RegisterObjectMethod("Mat3", "Vector3 multiplyVec3(const Vector3 &in)", asMETHOD(Mat3, multiplyVec3), asCALL_THISCALL);

    // Register Mat4
    engine->RegisterObjectType("Mat4", sizeof(Mat4), asOBJ_VALUE | asOBJ_POD | asGetTypeTraits<Mat4>());
    engine->RegisterObjectBehaviour("Mat4", asBEHAVE_CONSTRUCT, "void f()", asFUNCTION(ConstructMat4), asCALL_CDECL_OBJFIRST);
    engine->RegisterObjectBehaviour("Mat4", asBEHAVE_CONSTRUCT, "void f(float)", asFUNCTION(ConstructMat4WithDiagonal), asCALL_CDECL_OBJFIRST);

    // Register Mat4 methods (use wrappers instead of overloaded operators)
    engine->RegisterObjectMethod("Mat4", "Mat4 multiplyMat4(const Mat4 &in)", asMETHOD(Mat4, multiplyMat4), asCALL_THISCALL);
    engine->RegisterObjectMethod("Mat4", "Vector4 multiplyVec4(const Vector4 &in)", asMETHOD(Mat4, multiplyVec4), asCALL_THISCALL);
}


void RegisterObject(asIScriptEngine* engine) {
    int r;

    // Register Object type
    r = engine->RegisterObjectType("Object", 0, asOBJ_REF | asOBJ_NOCOUNT);
    if (r < 0) {
        std::cerr << "Failed to register Object type. Error code: " << r << std::endl;
    }

    // Register Object methods
    r = engine->RegisterObjectMethod("Object", "void addChild(array<Object@>&)", asMETHOD(Object, addChild), asCALL_THISCALL);
    if (r < 0) {
        std::cerr << "Failed to register addChild for Object. Error code: " << r << std::endl;
    }

    r = engine->RegisterObjectMethod("Object", "array<Object@>@ returnChildren()", asMETHOD(Object, returnChildren), asCALL_THISCALL);
    if (r < 0) {
        std::cerr << "Failed to register returnChildren for Object. Error code: " << r << std::endl;
    }

    r = engine->RegisterObjectMethod("Object", "void updateSelfAndChild()", asMETHOD(Object, updateSelfAndChild), asCALL_THISCALL);
    if (r < 0) {
        std::cerr << "Failed to register updateSelfAndChild for Object. Error code: " << r << std::endl;
    }
}

void RegisterWorld(asIScriptEngine* engine) {
    int r;

    // Register World type as a reference type
    r = engine->RegisterObjectType("World", 0, asOBJ_REF);
    if (r < 0) {
        std::cerr << "Failed to register World type. Error code: " << r << std::endl;
        return;
    }

    // Register World factory function
    r = engine->RegisterObjectBehaviour("World", asBEHAVE_FACTORY, "World@ f()", asFUNCTION(WorldFactory), asCALL_CDECL);
    if (r < 0) {
        std::cerr << "Failed to register World factory function. Error code: " << r << std::endl;
        return;
    }

    // Register reference counting behaviors for World
    r = engine->RegisterObjectBehaviour("World", asBEHAVE_ADDREF, "void f()", asMETHOD(World, AddRef), asCALL_THISCALL);
    if (r < 0) {
        std::cerr << "Failed to register AddRef for World. Error code: " << r << std::endl;
    }

    r = engine->RegisterObjectBehaviour("World", asBEHAVE_RELEASE, "void f()", asMETHOD(World, Release), asCALL_THISCALL);
    if (r < 0) {
        std::cerr << "Failed to register Release for World. Error code: " << r << std::endl;
    }

    // Register World methods (including inherited methods from Object)
    r = engine->RegisterObjectMethod("World", "void addChild(array<Object@>&)", asMETHOD(Object, addChild), asCALL_THISCALL);
    if (r < 0) {
        std::cerr << "Failed to register addChild for World. Error code: " << r << std::endl;
    }

    r = engine->RegisterObjectMethod("World", "array<Object@>@ returnChildren()", asMETHOD(Object, returnChildren), asCALL_THISCALL);
    if (r < 0) {
        std::cerr << "Failed to register returnChildren for World. Error code: " << r << std::endl;
    }

    r = engine->RegisterObjectMethod("World", "void updateSelfAndChild()", asMETHOD(Object, updateSelfAndChild), asCALL_THISCALL);
    if (r < 0) {
        std::cerr << "Failed to register updateSelfAndChild for World. Error code: " << r << std::endl;
    }

    // Register World-specific methods
    r = engine->RegisterObjectMethod("World", "void draw()", asMETHOD(World, draw), asCALL_THISCALL);
    if (r < 0) {
        std::cerr << "Failed to register draw for World. Error code: " << r << std::endl;
    }
}

void RegisterTransform(asIScriptEngine* engine) 
{
    int r;

    // Register Transform type as a reference type
    r = engine->RegisterObjectType("Transform", 0, asOBJ_REF | asOBJ_NOCOUNT);
    if (r < 0) {
        std::cerr << "Failed to register Transform type. Error code: " << r << std::endl;
        return;
    }

    // Register Transform methods
    r = engine->RegisterObjectMethod("Transform", "Mat4 getLocalModelMatrix()", asMETHOD(Transform, getLocalModelMatrix), asCALL_THISCALL);
    if (r < 0) {
        std::cerr << "Failed to register getLocalModelMatrix for Transform. Error code: " << r << std::endl;
    }

    r = engine->RegisterObjectMethod("Transform", "void computeModelMatrix()", asMETHOD(Transform, computeModelMatrix), asCALL_THISCALL);
    if (r < 0) {
        std::cerr << "Failed to register computeModelMatrix for Transform. Error code: " << r << std::endl;
    }

    r = engine->RegisterObjectMethod("Transform", "void computeModelMatrix(const Mat4 &in)", asMETHOD(Transform, computeModelMatrix), asCALL_THISCALL);
    if (r < 0) {
        std::cerr << "Failed to register computeModelMatrix (with parent matrix) for Transform. Error code: " << r << std::endl;
    }

    r = engine->RegisterObjectMethod("Transform", "void setLocalPosition(const Vector3 &in)", asMETHOD(Transform, setLocalPosition), asCALL_THISCALL);
    if (r < 0) {
        std::cerr << "Failed to register setLocalPosition for Transform. Error code: " << r << std::endl;
    }

    r = engine->RegisterObjectMethod("Transform", "Vector3& getLocalPosition()", asMETHOD(Transform, getLocalPosition), asCALL_THISCALL);
    if (r < 0) {
        std::cerr << "Failed to register getLocalPosition for Transform. Error code: " << r << std::endl;
    }

    r = engine->RegisterObjectMethod("Transform", "Mat4& getLocalMatrix()", asMETHOD(Transform, getLocalMatrix), asCALL_THISCALL);
    if (r < 0) {
        std::cerr << "Failed to register getLocalMatrix for Transform. Error code: " << r << std::endl;
    }

    r = engine->RegisterObjectMethod("Transform", "bool isDirty() const", asMETHOD(Transform, isDirty), asCALL_THISCALL);
    if (r < 0) {
        std::cerr << "Failed to register isDirty for Transform. Error code: " << r << std::endl;
    }
}

void RegisterArray(asIScriptEngine* engine) 
{
    RegisterScriptArray(engine, true);
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

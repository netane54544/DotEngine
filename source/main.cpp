#include "bindings.h"
#include "scriptbuilder.h"
#include "scriptstdstring.h"
#include "angelscript.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <regex>

#define ERROR_RETURN -1
#define PROGRAM_END 0

using namespace std;

// Error callback for AngelScript
void MessageCallback(const asSMessageInfo* msg, void* param) 
{
    const char* type = "ERROR";
    if (msg->type == asMSGTYPE_WARNING) type = "WARNING";
    else if (msg->type == asMSGTYPE_INFORMATION) type = "INFO";
    cout << msg->section << " (" << msg->row << ", " << msg->col << ") : " << type << " : " << msg->message << endl;
}

// Function to read a file into a string
string ReadFile(const string& filename) 
{
    ifstream file(filename);

    if (!file.is_open()) 
    {
        cerr << "Failed to open file: " << filename << endl;
        return "";
    }

    stringstream buffer;
    buffer << file.rdbuf();

    return buffer.str();
}

int main(int argc, char* argv[]) 
{
    if (argc < 2) 
    {
        cerr << "Usage: " << argv[0] << " <script file>" << endl;
        return ERROR_RETURN;
    }
    else if(argc > 2)
    {
        cerr << "Too much arguments" << endl;
        return ERROR_RETURN;
    }

    if (!glfwInit())
    {
        cerr << "Error: Couldn't intialize OpenGL" << endl;
        return ERROR_RETURN;
    }

    // Create the AngelScript engine
    asIScriptEngine* engine = asCreateScriptEngine();
    bool foundEx = false;

    // Set the message callback
    engine->SetMessageCallback(asFUNCTION(MessageCallback), 0, asCALL_CDECL);

    // Register functions to the engine
    RegisterStdString(engine);
    RegisterVectors(engine);
    RegisterPrintFunction(engine);

    RegisterGameWindow(engine);

    // Load and build the script
    CScriptBuilder builder;
    if (builder.StartNewModule(engine, "DotCore") < 0) 
    {
        cerr << "Failed to start new module." << endl;
        return ERROR_RETURN;
    }

    if (builder.AddSectionFromFile(argv[1]) < 0) 
    {
        cerr << "Failed to add script section." << endl;
        return ERROR_RETURN;
    }

    if (builder.BuildModule() < 0) 
    {
        cerr << "Failed to build module." << endl;
        return ERROR_RETURN;
    }

    // Get the function and execute it
    asIScriptModule* mod = engine->GetModule("DotCore");
    asIScriptFunction* func = mod->GetFunctionByDecl("void main()");
    if (func == nullptr) 
    {
        cerr << "Function 'void main()' not found." << endl;
        return ERROR_RETURN;
    }

    asIScriptContext* ctx = engine->CreateContext();
    ctx->Prepare(func);
    
    int r = ctx->Execute();

    if (r == asEXECUTION_EXCEPTION)
    {
        asIScriptFunction* func = ctx->GetExceptionFunction();
        const char* funcName = func->GetDeclaration();
        int line = ctx->GetExceptionLineNumber();
        const char* exceptionString = ctx->GetExceptionString();
        foundEx = true;

        cout << "Exception in function: " << funcName << endl;
        cout << "At line: " << line << std::endl;
        cerr << "Exception message: " << exceptionString << endl;
    }
    

    if(!foundEx)
        if(Game_Window::window != nullptr && Game_Window::runLoop)
            Game_Window::runInternalLoop();

    // Clean up
    ctx->Release();
    engine->ShutDownAndRelease();

    return PROGRAM_END;
}

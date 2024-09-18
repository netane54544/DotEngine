#include "bindings.h"
#include "scriptbuilder.h"
#include "scriptstdstring.h"
#include "angelscript.h"
#include <iostream>
#include <fstream>
#include <sstream>

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
string ReadFile(const string& filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Failed to open file: " << filename << endl;
        return "";
    }
    stringstream buffer;
    buffer << file.rdbuf();
    return buffer.str();
}

int main(int argc, char* argv[]) 
{
    if (argc < 2) {
        std::cerr << "Usage: " << argv[0] << " <script file>" << std::endl;
        return -1;
    }

    std::string script_file = argv[1];

    // Create the AngelScript engine
    asIScriptEngine* engine = asCreateScriptEngine();

    // Set the message callback
    engine->SetMessageCallback(asFUNCTION(MessageCallback), 0, asCALL_CDECL);

    // Register the string type
    RegisterStdString(engine);

    // Register Game_Window and Print function
    RegisterGameWindow(engine);
    RegisterPrintFunction(engine);

    // Load and build the script
    CScriptBuilder builder;
    if (builder.StartNewModule(engine, "MyModule") < 0) {
        std::cerr << "Failed to start new module." << std::endl;
        return -1;
    }

    if (builder.AddSectionFromFile(script_file.c_str()) < 0) {
        std::cerr << "Failed to add script section." << std::endl;
        return -1;
    }

    if (builder.BuildModule() < 0) {
        std::cerr << "Failed to build module." << std::endl;
        return -1;
    }

    // Get the function and execute it
    asIScriptModule* mod = engine->GetModule("MyModule");
    asIScriptFunction* func = mod->GetFunctionByDecl("void main()");
    if (func == nullptr) {
        std::cerr << "Function 'void main()' not found." << std::endl;
        return -1;
    }

    asIScriptContext* ctx = engine->CreateContext();
    ctx->Prepare(func);
    int r = ctx->Execute();
    if (r != asEXECUTION_FINISHED) {
        std::cerr << "Script execution failed." << std::endl;
        if (r == asEXECUTION_EXCEPTION) {
            std::cerr << "Exception: " << ctx->GetExceptionString() << std::endl;
        }
    }

    // Clean up
    ctx->Release();
    engine->ShutDownAndRelease();

    return 0;
}

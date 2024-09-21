void TestPrint() 
{
    // Test printing a string
    Print("Testing Print function with strings and vectors:");

    // Test with Vector2
    Vector2 v2(1.0, 2.0);
    Print("Vector2 test:");
    Print(v2); // Should output: Vector2(1.0, 2.0)

    // Test with Vector3
    Vector3 v3(1.0, 2.0, 3.0);
    Print("Vector3 test:");
    Print(v3); // Should output: Vector3(1.0, 2.0, 3.0)

    // Test with Vector4
    Vector4 v4(1.0, 2.0, 3.0, 4.0);
    Print("Vector4 test:");
    Print(v4); // Should output: Vector4(1.0, 2.0, 3.0, 4.0)
}


void main() 
{
    // Create a Game_Window instance
    Game_Window window("My Game", Vector2(1200, 800), false);
    
    // Run the game loop
    window.gameLoop();
    window.setColorRGBA(Vector4(0.2f, 0.1f, 0.0f, 0.0f));

    // Get the window dimensions
    int width = window.getWidth();
    int height = window.getHeight();
    
    // Print the window dimensions
    Print("Game Window Width: " + width);
    Print("Game Window Height: " + height);
    //TestPrint();
}

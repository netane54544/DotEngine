void main() 
{
    // Create a Game_Window instance
    Game_Window window("My Game", 800, 600, false);
    
    // Run the game loop
    window.gameLoop();
    
    // Get the window dimensions
    int width = window.getWidth();
    int height = window.getHeight();
    
    // Print the window dimensions
    Print("Game Window Width: " + width);
    Print("Game Window Height: " + height);
}

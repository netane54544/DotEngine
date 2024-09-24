void main() {
    // Create a World object using the factory function
    World@ world = World();

    // Retrieve the children from the World and print the count
    array<Object@> worldChildren = world.returnChildren();
    Print("Number of children in world: " + worldChildren.length());

    // Call updateSelfAndChild on the world
    world.updateSelfAndChild();

    // Call draw on the world
    world.draw();

}
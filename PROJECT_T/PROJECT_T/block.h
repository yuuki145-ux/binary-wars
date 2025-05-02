#pragma once
#include <raylib.h>

// The Block class represents a block entity in the game.
// It includes properties such as position and provides methods for drawing and retrieving its rectangle.
class Block {
public:
    // Constructor to initialize a Block with a specific position.
    // position: The initial position of the block in the game world.
    Block(Vector2 position);

    // Draws the block on the screen using its current position.
    void Draw();

    // Returns the rectangle representing the block's position and size.
    // Useful for collision detection or rendering calculations.
    Rectangle getRect();

private:
    // The current position of the block in the game world.
    Vector2 position;
};

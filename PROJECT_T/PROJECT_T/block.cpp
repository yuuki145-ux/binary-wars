#include "block.h"

// Constructor: Initializes the block's position.
// Parameters:
// - position: The initial position of the block (Vector2).
Block::Block(Vector2 position)
{
    this->position = position; // Set the block's position.
}

// Draws the block on the screen at its current position.
void Block::Draw() {
    // Draw a small rectangle representing the block.
    // The block is drawn with a width and height of 3, and a yellow color.
    DrawRectangle(position.x, position.y, 3, 3, { 243, 216, 63, 255 });
}

// Returns a rectangle representing the block's position and size.
// This is useful for collision detection with other game elements.
Rectangle Block::getRect()
{
    Rectangle rect;
    rect.x = position.x;    // Set the x-coordinate of the rectangle.
    rect.y = position.y;    // Set the y-coordinate of the rectangle.
    rect.width = 3;         // Set the width of the rectangle (matches the block's width).
    rect.height = 3;        // Set the height of the rectangle (matches the block's height).
    return rect;            // Return the rectangle.
}

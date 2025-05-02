#include "bullet.h"
#include <iostream>

// Constructor: Initializes the laser's position, speed, and active state.
Laser::Laser(Vector2 position, int speed)
{
    this->position = position; // Set the initial position of the laser.
    this->speed = speed;       // Set the speed of the laser (positive for downward, negative for upward).
    active = true;             // Mark the laser as active when created.
}

// Draws the laser on the screen if it is active.
void Laser::Draw() {
    if (active) {
        // Draw a rectangle representing the laser at its current position.
        // The laser is drawn with a width of 4, height of 15, and a yellow color.
        DrawRectangle(position.x, position.y, 4, 15, { 243, 216, 63, 255 });
    }
}

// Returns a rectangle representing the laser's position and size.
// This is useful for collision detection with other game elements.
Rectangle Laser::getRect()
{
    Rectangle rect;
    rect.x = position.x;    // Set the x-coordinate of the rectangle.
    rect.y = position.y;    // Set the y-coordinate of the rectangle.
    rect.width = 4;         // Set the width of the rectangle (matches the laser's width).
    rect.height = 15;       // Set the height of the rectangle (matches the laser's height).
    return rect;            // Return the rectangle.
}

// Updates the laser's position and checks if it is still within the screen bounds.
void Laser::Update() {
    position.y += speed; // Move the laser vertically based on its speed.

    if (active) { // Only check bounds if the laser is active.
        // Deactivate the laser if it moves out of the screen bounds.
        if (position.y > GetScreenHeight() - 100 || position.y < 25) {
            active = false;
        }
    }
}

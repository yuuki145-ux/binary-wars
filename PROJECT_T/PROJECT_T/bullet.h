#pragma once
#include <raylib.h>

// The Laser class represents a laser projectile in the game.
// It handles the laser's position, movement, rendering, and collision detection.
class Laser {
public:
    // Constructor: Initializes the laser's position and speed.
    // Parameters:
    // - position: The initial position of the laser (Vector2).
    // - speed: The speed at which the laser moves (int).
    Laser(Vector2 position, int speed);

    // Updates the laser's position based on its speed.
    // Typically called every frame to move the laser.
    void Update();

    // Draws the laser on the screen at its current position.
    void Draw();

    // Returns a rectangle representing the laser's position and size.
    // Useful for collision detection with other game elements.
    Rectangle getRect();

    // Indicates whether the laser is currently active.
    // If false, the laser should be removed from the game.
    bool active;

private:
    // The current position of the laser on the screen.
    Vector2 position;

    // The speed at which the laser moves.
    // A positive value typically moves the laser downward,
    // while a negative value moves it upward.
    int speed;
};

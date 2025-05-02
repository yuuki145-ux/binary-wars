#pragma once
#include <raylib.h>
#include "bullet.h"
#include <vector>

using namespace std;

// The Spaceship class represents the player's spaceship in the game.
// It handles movement, firing lasers, and rendering the spaceship.
class Spaceship {
public:
    // Constructor: Initializes the spaceship's properties and resources.
    Spaceship();

    // Destructor: Cleans up resources used by the spaceship.
    ~Spaceship();

    // Draws the spaceship on the screen at its current position.
    void Draw();

    // Moves the spaceship to the left by a fixed amount.
    // Ensures the spaceship does not move out of bounds.
    void MoveLeft();

    // Moves the spaceship to the right by a fixed amount.
    // Ensures the spaceship does not move out of bounds.
    void MoveRight();

    // Fires a laser from the spaceship's current position.
    // Ensures a cooldown period between consecutive shots.
    void FireLaser();

    // Returns a rectangle representing the spaceship's position and size.
    // Useful for collision detection.
    Rectangle getRect();

    // Resets the spaceship's position and state to its initial values.
    void Reset();

    // A collection of lasers fired by the spaceship.
    vector<Laser> lasers;

private:
    // The texture used to render the spaceship.
    Texture2D image;

    // The current position of the spaceship on the screen.
    Vector2 position;

    // The time (in seconds) when the spaceship last fired a laser.
    double lastFireTime;

    // The sound effect played when the spaceship fires a laser.
    Sound laserSound;
};

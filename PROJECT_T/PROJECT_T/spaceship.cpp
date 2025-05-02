#include "spaceship.h"

// Constructor: Initializes the spaceship's properties and resources.
Spaceship::Spaceship()
{
    // Load the spaceship texture from the specified file path.
    image = LoadTexture("C:/Users/jayso/OneDrive/Desktop/PROJECT_T/PROJECT_T/pictures/spaceship2.png");

    // Set the initial position of the spaceship to be horizontally centered
    // and slightly above the bottom of the screen.
    position.x = (GetScreenWidth() - image.width) / 2;
    position.y = GetScreenHeight() - image.height - 100;

    // Initialize the last fire time to 0.
    lastFireTime = 0.0;

    // Load the laser sound effect from the specified file path.
    laserSound = LoadSound("C:/Users/jayso/Downloads/shootsound1.ogg");
}

// Destructor: Cleans up resources used by the spaceship.
Spaceship::~Spaceship() {
    // Unload the spaceship texture to free memory.
    UnloadTexture(image);

    // Unload the laser sound effect to free memory.
    UnloadSound(laserSound);
}

// Draws the spaceship on the screen at its current position.
void Spaceship::Draw() {
    DrawTextureV(image, position, WHITE);
}

// Moves the spaceship to the left by a fixed amount.
// Ensures the spaceship does not move out of bounds.
void Spaceship::MoveLeft() {
    position.x -= 7; // Move left by 7 units.
    if (position.x < 25) { // Prevent the spaceship from going beyond the left boundary.
        position.x = 25;
    }
}

// Moves the spaceship to the right by a fixed amount.
// Ensures the spaceship does not move out of bounds.
void Spaceship::MoveRight() {
    position.x += 7; // Move right by 7 units.
    if (position.x > GetScreenWidth() - image.width - 25) { // Prevent the spaceship from going beyond the right boundary.
        position.x = GetScreenWidth() - image.width - 25;
    }
}

// Fires a laser from the spaceship's current position.
// Ensures a cooldown period of 0.2 seconds between consecutive shots.
void Spaceship::FireLaser()
{
    if (GetTime() - lastFireTime >= 0.2) { // Check if enough time has passed since the last shot.
        // Add a new laser to the lasers vector, starting from the spaceship's position.
        lasers.push_back(Laser({ position.x + image.width / 2 - 2, position.y }, -7));

        // Update the last fire time to the current time.
        lastFireTime = GetTime();

        // Play the laser sound effect.
        PlaySound(laserSound);
    }
}

// Returns a rectangle representing the spaceship's position and size.
// Useful for collision detection.
Rectangle Spaceship::getRect()
{
    return { position.x, position.y, float(image.width), float(image.height) };
}

// Resets the spaceship's position and clears all active lasers.
void Spaceship::Reset()
{
    // Reset the position to the initial centered position.
    position.x = (GetScreenWidth() - image.width) / 2.0f;
    position.y = GetScreenHeight() - image.height - 100;

    // Clear the lasers vector to remove all active lasers.
    lasers.clear();
}

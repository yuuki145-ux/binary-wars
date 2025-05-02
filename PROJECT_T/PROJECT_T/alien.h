#pragma once
#include <raylib.h>

// The Alien class represents an alien entity in the game.
// It includes properties such as type and position, and provides methods for updating, drawing, and managing the alien.
class Alien {
public:
    // Constructor to initialize an Alien with a specific type and position.
    Alien(int type, Vector2 position);

    // Updates the alien's position or state based on the given direction.
    // direction: The direction in which the alien should move or update.
    void Update(int direction);

    // Draws the alien on the screen using its current position and type.
    void Draw();

    // Returns the type of the alien.
    // The type determines the alien's appearance or behavior.
    int GetType();

    // Unloads the static images (textures) used by all Alien instances.
    // This should be called to free resources when they are no longer needed.
    static void UnloadImages();

    // Returns the rectangle representing the alien's current position and size.
    // Useful for collision detection or rendering calculations.
    Rectangle getRect();

    // Static array of textures representing different alien types.
    // Each index corresponds to a specific alien type.
    static Texture2D parcel[3];

    // The type of the alien, determining its appearance or behavior.
    int type;

    // The current position of the alien in the game world.
    Vector2 position;

private:
};

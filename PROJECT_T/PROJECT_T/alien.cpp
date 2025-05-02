#include "alien.h"

// Initialize the static array of textures for different alien types.
Texture2D Alien::parcel[3] = {};

// Constructor for the Alien class.
// Initializes the alien's type and position, and loads the texture for the specified type if not already loaded.
Alien::Alien(int type, Vector2 position)
{
    this->type = type; // Set the alien's type.
    this->position = position; // Set the alien's initial position.

    // Check if the texture for the given type is not already loaded.
    if (parcel[type - 1].id == 0) {
        // Load the appropriate texture based on the alien type.
        switch (type) {
        case 1:
            parcel[0] = LoadTexture("C:/Users/jayso/OneDrive/Desktop/PROJECT_T/PROJECT_T/pictures/alien_1.png");
            break;
        case 2:
            parcel[1] = LoadTexture("C:/Users/jayso/OneDrive/Desktop/PROJECT_T/PROJECT_T/pictures/alien2.png");
            break;
        case 3:
            parcel[2] = LoadTexture("C:/Users/jayso/OneDrive/Desktop/PROJECT_T/PROJECT_T/pictures/alien1.png");
            break;
        default:
            // Default to the first texture if the type is invalid.
            parcel[0] = LoadTexture("C:/Users/jayso/OneDrive/Desktop/PROJECT_T/PROJECT_T/alien1.png");
            break;
        }
    }
}

// Draws the alien on the screen using its texture and position.
void Alien::Draw() {
    DrawTextureV(parcel[type - 1], position, WHITE);
}

// Returns the type of the alien.
int Alien::GetType() {
    return type;
}

// Unloads all textures used by the Alien class.
// This should be called to free resources when the textures are no longer needed.
void Alien::UnloadImages()
{
    for (int i = 0; i < 4; i++) {
        UnloadTexture(parcel[i]);
    }
}

// Returns a rectangle representing the alien's position and size.
// Useful for collision detection or rendering calculations.
Rectangle Alien::getRect()
{
    return { position.x, position.y,
    float(parcel[type - 1].width),
    float(parcel[type - 1].height)
    };
}

// Updates the alien's position based on the given direction.
// direction: The amount to move the alien along the x-axis.
void Alien::Update(int direction) {
    position.x += direction;
}

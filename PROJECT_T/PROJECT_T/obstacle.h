#pragma once
#include <vector>
#include "block.h"
using namespace std;
// The Obstacle class represents a collection of blocks that form an obstacle in the game.
// Obstacles are used as barriers to protect the player's spaceship or to obstruct enemy movement.
class Obstacle {
public:
    // Constructor: Initializes the obstacle's position and creates its blocks.
    // Parameters:
    // - position: The initial position of the obstacle (Vector2).
    Obstacle(Vector2 position);

    // Draws the obstacle by rendering all its blocks on the screen.
    void Draw();

    // The position of the obstacle on the screen.
    Vector2 position;

    // A collection of blocks that make up the obstacle.
    vector<Block> blocks;

    // A static grid that defines the layout of blocks within the obstacle.
    // Each element in the grid represents whether a block exists at a specific position.
    static vector<vector<int>> grid;

private:
    // No private members or methods are defined in this class.
};


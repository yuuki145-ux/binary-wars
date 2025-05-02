#include "obstacle.h"

// Static grid defining the layout of blocks within an obstacle.
// Each element in the grid represents whether a block exists (1) or not (0) at a specific position.
std::vector<std::vector<int>> Obstacle::grid = {
   {0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0},
   {0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0},
   {0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0},
   {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
   {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
   {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
   {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
   {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
   {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
   {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
   {0, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 0},
   {0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0},
   {0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0}
};

// Constructor: Initializes the obstacle's position and creates its blocks based on the grid layout.
// Parameters:
// - position: The top-left position of the obstacle (Vector2).
Obstacle::Obstacle(Vector2 position)
{
    this->position = position; // Set the obstacle's position.

    // Iterate through the grid to create blocks where grid[row][column] == 1.
    for (unsigned int row = 0; row < grid.size(); ++row) {
        for (unsigned int column = 0; column < grid[0].size(); ++column) {
            if (grid[row][column] == 1) { // Check if a block exists at this grid position.
                // Calculate the block's position based on the obstacle's position and grid coordinates.
                float pos_x = position.x + column * 3;
                float pos_y = position.y + row * 3;

                // Create a block at the calculated position and add it to the blocks vector.
                Block block = Block({ pos_x, pos_y });
                blocks.push_back(block);
            }
        }
    }
}

// Draws the obstacle by rendering all its blocks on the screen.
void Obstacle::Draw() {
    for (auto& block : blocks) { // Iterate through all blocks in the obstacle.
        block.Draw(); // Draw each block.
    }
}


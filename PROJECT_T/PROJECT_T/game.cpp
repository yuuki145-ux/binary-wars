#include "game.h"
#include <iostream>
#include <fstream>

using namespace std;

// Constructor: Initializes the game by loading resources and starting the game.
Game::Game()
{
    // Load background music and explosion sound effects.
    music = LoadMusicStream("C:/Users/jayso/OneDrive/Desktop/PROJECT_T/PROJECT_T/sounds/bgsounds.ogg");
    explosionSound = LoadSound("C:/Users/jayso/OneDrive/Desktop/PROJECT_T/PROJECT_T/sounds/explosion.ogg");

    // Start playing the background music.
	PlayMusicStream(music);	SetMusicVolume(music, 0.9f); // Set the volume of the background music.

    // Initialize the game state.
    InitGame();
}

// Destructor: Cleans up resources used by the game.
Game::~Game() {
    Alien::UnloadImages(); // Unload alien images.
    UnloadMusicStream(music); // Unload background music.
    UnloadSound(explosionSound); // Unload explosion sound.
}

// Updates the game state, including player, aliens, lasers, and collisions.
void Game::Update() {
    if (run) {
        double currentTime = GetTime();

        // Spawn the mystery ship at random intervals.
        if (currentTime - timeLastSpawn > mysteryShipSpawnInterval) {
            mysteryship.Spawn();
            timeLastSpawn = GetTime();
            mysteryShipSpawnInterval = GetRandomValue(10, 20);
        }

        // Update the spaceship's lasers.
        for (auto& laser : spaceship.lasers) {
            laser.Update();
        }

        // Move the aliens and handle their laser shooting.
        MoveAliens();
        AlienShootLaser();

        // Update the alien lasers.
        for (auto& laser : alienLasers) {
            laser.Update();
        }

        // Remove inactive lasers from the game.
        DeleteInactiveLasers();

        // Update the mystery ship's state.
        mysteryship.Update();

        // Check for collisions between game elements.
        CheckForCollisions();
    }
    else {
        // Restart the game if the player presses Enter after a game over.
        if (IsKeyDown(KEY_ENTER)) {
            Reset();
            InitGame();
        }
    }
}


// Draws all game elements on the screen.
void Game::Draw() {
    spaceship.Draw(); // Draw the spaceship.

    // Draw the spaceship's lasers.
    for (auto& laser : spaceship.lasers) {
        laser.Draw();
    }

    // Draw the obstacles.
    for (auto& obstacle : obstacles) {
        obstacle.Draw();
    }

    // Draw the aliens.
    for (auto& alien : aliens) {
        alien.Draw();
    }

    // Draw the alien lasers.
    for (auto& laser : alienLasers) {
        laser.Draw();
    }

    // Draw the mystery ship.
    mysteryship.Draw();
}

// Handles user input for controlling the spaceship.
void Game::HandleInput() {
    if (run) {
        if (IsKeyDown(KEY_A)) {
            spaceship.MoveLeft(); // Move spaceship left.
        }
        else if (IsKeyDown(KEY_D)) {
            spaceship.MoveRight(); // Move spaceship right.
        }
        else if (IsKeyDown(KEY_SPACE)) {
            spaceship.FireLaser(); // Fire a laser.
        }
    }
}

// Removes inactive lasers from the game.
void Game::DeleteInactiveLasers()
{
    // Remove inactive spaceship lasers.
    for (auto it = spaceship.lasers.begin(); it != spaceship.lasers.end();) {
        if (!it->active) {
            it = spaceship.lasers.erase(it);
        }
        else {
            ++it;
        }
    }

    // Remove inactive alien lasers.
    for (auto it = alienLasers.begin(); it != alienLasers.end();) {
        if (!it->active) {
            it = alienLasers.erase(it);
        }
        else {
            ++it;
        }
    }
}

// Creates and initializes obstacles for the game.
vector<Obstacle> Game::CreateObstacles()
{
    int obstacleWidth = Obstacle::grid[0].size() * 3;
    float gap = (GetScreenWidth() - (4 * obstacleWidth)) / 5;

    for (int i = 0; i < 4; i++) {
        float offsetX = (i + 1) * gap + i * obstacleWidth;
        obstacles.push_back(Obstacle({ offsetX, float(GetScreenHeight() - 200) }));
    }
    return obstacles;
}

// Creates and initializes aliens for the game.
vector<Alien> Game::CreateAliens()
{
    vector<Alien> aliens;
    for (int row = 0; row < 5; row++) {
        for (int column = 0; column < 11; column++) {
            int alienType;

            // Assign alien type based on row.
            if (row == 0) {
                alienType = 3;
            }
            else if (row == 1 || row == 2) {
                alienType = 2;
            }
            else {
                alienType = 1;
            }

            // Calculate alien position.
            float x = 75 + column * 55;
            float y = 110 + row * 55;
            aliens.push_back(Alien(alienType, { x, y }));
        }
    }
    return aliens;
}

// Moves the aliens horizontally and adjusts their direction if needed.
void Game::MoveAliens() {
    for (auto& alien : aliens) {
        // Check if aliens hit the screen boundaries.
        if (alien.position.x + alien.parcel[alien.type - 1].width > GetScreenWidth() - 25) {
            aliensDirection = -1; // Change direction to left.
            MoveDownAliens(4); // Move aliens down.
        }
        if (alien.position.x < 25) {
            aliensDirection = 1; // Change direction to right.
            MoveDownAliens(4); // Move aliens down.
        }

        alien.Update(aliensDirection); // Update alien position.
    }
}

// Moves all aliens downward by a specified distance.
void Game::MoveDownAliens(int distance)
{
    for (auto& alien : aliens) {
        alien.position.y += distance;
    }
}

// Handles alien laser shooting at random intervals.
void Game::AlienShootLaser()
{
    double currentTime = GetTime();
    if (currentTime - timeLastAlienFired >= alienLaserShootInterval && !aliens.empty()) {
        int randomIndex = GetRandomValue(0, aliens.size() - 1);
        Alien& alien = aliens[randomIndex];

        // Add a new laser fired by the alien.
        alienLasers.push_back(Laser({ alien.position.x + alien.parcel[alien.type - 1].width / 2,
                                    alien.position.y + alien.parcel[alien.type - 1].height }, 6));
        timeLastAlienFired = GetTime();
    }
}

// Checks for collisions between game elements (e.g., lasers, aliens, obstacles).
void Game::CheckForCollisions()
{
    // Check collisions for spaceship lasers.
    for (auto& laser : spaceship.lasers) {
        auto it = aliens.begin();
        while (it != aliens.end()) {
            if (CheckCollisionRecs(it->getRect(), laser.getRect())) {
                PlaySound(explosionSound);

                // Update score based on alien type.
                if (it->type == 1) {
                    score += 100;
                }
                else if (it->type == 2) {
                    score += 200;
                }
                else if (it->type == 3) {
                    score += 300;
                }
                checkForHighscore();

                it = aliens.erase(it); // Remove the alien.
                laser.active = false; // Deactivate the laser.
            }
            else {
                ++it;
            }
        }

        // Check collisions with obstacles.
        for (auto& obstacle : obstacles) {
            auto it = obstacle.blocks.begin();
            while (it != obstacle.blocks.end()) {
                if (CheckCollisionRecs(it->getRect(), laser.getRect())) {
                    it = obstacle.blocks.erase(it); // Remove the block.
                    laser.active = false; // Deactivate the laser.
                }
                else {
                    ++it;
                }
            }
        }

        // Check collisions with the mystery ship.
        if (CheckCollisionRecs(mysteryship.getRect(), laser.getRect())) {
            mysteryship.alive = false;
            laser.active = false;
            score += 500; // Add bonus points for hitting the mystery ship.
            checkForHighscore();
            PlaySound(explosionSound);
        }
    }

    // Check collisions for alien lasers.
    for (auto& laser : alienLasers) {
        if (CheckCollisionRecs(laser.getRect(), spaceship.getRect())) {
            laser.active = false;
            lives--; // Decrease player lives.
            if (lives == 0) {
                GameOver(); // End the game if lives reach 0.
            }
        }

        // Check collisions with obstacles.
        for (auto& obstacle : obstacles) {
            auto it = obstacle.blocks.begin();
            while (it != obstacle.blocks.end()) {
                if (CheckCollisionRecs(it->getRect(), laser.getRect())) {
                    it = obstacle.blocks.erase(it); // Remove the block.
                    laser.active = false; // Deactivate the laser.
                }
                else {
                    ++it;
                }
            }
        }
    }

    // Check collisions between aliens and obstacles.
    for (auto& alien : aliens) {
        for (auto& obstacle : obstacles) {
            auto it = obstacle.blocks.begin();
            while (it != obstacle.blocks.end()) {
                if (CheckCollisionRecs(it->getRect(), alien.getRect())) {
                    it = obstacle.blocks.erase(it); // Remove the block.
                }
                else {
                    ++it;
                }
            }
        }

        // Check collisions between aliens and the spaceship.
        if (CheckCollisionRecs(alien.getRect(), spaceship.getRect())) {
            GameOver(); // End the game if an alien collides with the spaceship.
        }
    }
}

// Ends the game by setting the run flag to false.
void Game::GameOver()
{
    run = false;
}

// Initializes the game state, including obstacles, aliens, and other elements.
void Game::InitGame()
{
    obstacles = CreateObstacles(); // Create obstacles.
    aliens = CreateAliens(); // Create aliens.
    aliensDirection = 1; // Set initial alien movement direction.
    timeLastAlienFired = 0.0; // Reset alien laser timer.
    timeLastSpawn = 0.0; // Reset mystery ship spawn timer.
    lives = 3; // Set initial player lives.
    score = 0; // Reset score.
    highscore = loadHighscoreFromFile(); // Load high score from file.
    run = true; // Start the game.
    mysteryShipSpawnInterval = GetRandomValue(10, 20); // Set random spawn interval for the mystery ship.
}

// Checks if the current score is a new high score and saves it if true.
void Game::checkForHighscore()
{
    if (score > highscore) {
        highscore = score;
        saveHighscoreToFile(highscore);
    }
}

// Saves the high score to a file.
void Game::saveHighscoreToFile(int highscore)
{
   ofstream highscoreFile("highscore.txt");
    if (highscoreFile.is_open()) {
        highscoreFile << highscore;
        highscoreFile.close();
    }
    else {
        cerr << "Failed to save highscore to file" << endl;
    }
}

// Loads the high score from a file.
int Game::loadHighscoreFromFile() {
    int loadedHighscore = 0;
    ifstream highscoreFile("highscore.txt");
    if (highscoreFile.is_open()) {
        highscoreFile >> loadedHighscore;
        highscoreFile.close();
    }
    else {
       cerr << "Failed to load highscore from file." << endl;
    }
    return loadedHighscore;
}

// Resets the game state by clearing all active elements and resetting the spaceship.
void Game::Reset() {
    spaceship.Reset(); // Reset the spaceship.
    aliens.clear(); // Clear all aliens.
    alienLasers.clear(); // Clear all alien lasers.
    obstacles.clear(); // Clear all obstacles.
}

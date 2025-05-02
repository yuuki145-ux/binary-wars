#pragma once
#include "spaceship.h"
#include "obstacle.h"
#include "alien.h"
#include "mysteryparcel.h"

using namespace std;

// The Game class manages the overall game logic, state, and interactions.
class Game {
public:
    // Constructor: Initializes the game state and resources.
    Game();

    // Destructor: Cleans up resources used by the game.
    ~Game();

    // Draws all game elements on the screen.
    void Draw();

    // Updates the game state, including player, enemies, and other elements.
    void Update();

    // Resets the game state to its initial values.
    void Reset(); // Moved from private to public

    // Handles user input for controlling the game.
    void HandleInput();

    // Indicates whether the game is currently running.
    bool run;

    // The number of lives the player has remaining.
    int lives;

    // The player's current score.
    int score;

    // The highest score achieved in the game.
    int highscore;

    // Background music for the game.
    Music music;

private:
    // Removes inactive lasers from the game.
    void DeleteInactiveLasers();

    // Creates and initializes obstacles for the game.
    vector<Obstacle> CreateObstacles();

    // Creates and initializes aliens for the game.
    vector<Alien> CreateAliens();

    // Moves the aliens horizontally across the screen.
    void MoveAliens();

    // Moves the aliens downward by a specified distance.
    void MoveDownAliens(int distance);

    // Handles the logic for aliens shooting lasers.
    void AlienShootLaser();

    // Checks for collisions between game elements (e.g., lasers, aliens, spaceship).
    void CheckForCollisions();

    // Ends the game and handles game-over logic.
    void GameOver();

    // Initializes the game, setting up all necessary elements.
    void InitGame();

    // Checks if the current score is a new high score.
    void checkForHighscore();

    // Saves the high score to a file.
    void saveHighscoreToFile(int highscore);

    // Loads the high score from a file.
    int loadHighscoreFromFile();

    // The player's spaceship.
    Spaceship spaceship;

    // A collection of obstacles in the game.
    vector<Obstacle> obstacles;

    // A collection of aliens in the game.
    vector<Alien> aliens;

    // The current direction of alien movement (e.g., left or right).
    int aliensDirection;

    // A collection of lasers fired by aliens.
    vector<Laser> alienLasers;

    // The interval (in seconds) between alien laser shots.
    constexpr static float alienLaserShootInterval = 0.35;

    // The time (in seconds) when the last alien fired a laser.
    float timeLastAlienFired;

    // The mystery ship that occasionally appears in the game.
    MysteryShip mysteryship;

    // The interval (in seconds) between mystery ship spawns.
    float mysteryShipSpawnInterval;

    // The time (in seconds) when the last mystery ship was spawned.
    float timeLastSpawn;

    // The sound effect played when an explosion occurs.
    Sound explosionSound;
};

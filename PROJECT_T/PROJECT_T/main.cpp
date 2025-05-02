#include <raylib.h>
#include "game.h"
#include <string>
#include <iostream> // For debug output

using namespace std;

// Function to format a number with leading zeros to match the specified width.
// For example, FormatWithLeadingZeros(42, 5) returns "00042".
string FormatWithLeadingZeros(int number, int width) {
    string numberText = to_string(number); // Convert the number to a string.
    int leadingZeros = width - numberText.length(); // Calculate the number of leading zeros needed.
    return string(leadingZeros, '0') + numberText; // Add leading zeros and return the result.
}

// Enum to represent the different states of the game.
enum Gamestate { MAIN_MENU, PLAYING, GAME_OVER };

int main()
{
    // Debug: Log program start
    cout << "Program started." << endl;

    // Variable to track whether the game is paused
    bool paused = false;

    // Define a custom gray color for the background.
    Color grey = { 29, 29, 27, 255 };

    // Offset values for adjusting the window size.
    int offset = 50;
    int windowWidth = 750; // Width of the game window.
    int windowHeight = 700; // Height of the game window.

    // Reinitialize the window with adjusted dimensions and title.
    InitWindow(windowWidth + offset, windowHeight + 2 * offset, "Binary Wars: Guardians of the CyberWorld");
    cout << "Window initialized with dimensions: " << windowWidth + offset << "x" << windowHeight + 2 * offset << endl;

    // Initialize the audio device for playing sounds and music.
    InitAudioDevice();
    cout << "Audio device initialized." << endl;

    // Load a custom font for rendering text in the game.
    Font font = LoadFontEx("C:/Users/jayso/OneDrive/Desktop/PROJECT_T/PROJECT_T/Font/monogram.ttf", 64, 0, 0);
    cout << "Font loaded." << endl;

    // Load the spaceship texture for rendering the player's lives.
    Texture2D spaceshipImage = LoadTexture("C:/Users/jayso/OneDrive/Desktop/PROJECT_T/PROJECT_T/pictures/spaceship2.png");
    cout << "Spaceship texture loaded." << endl;

    // Set the target frame rate for the game to 60 frames per second.
    SetTargetFPS(60);
    cout << "Target FPS set to 60." << endl;

    // Create an instance of the Game class to manage the game state and logic.
    Game game;
    cout << "Game instance created." << endl;

    // Variable to track the current state of the game.
    Gamestate gamestate = MAIN_MENU;

    // Main game loop. This loop runs until the window is closed.
    while (WindowShouldClose() == false)
    {
        // Debug: Log each frame
        cout << "Frame start." << endl;

        // Update the music stream to ensure smooth playback.
        UpdateMusicStream(game.music);

        // Begin drawing the current frame.
        BeginDrawing();

        // Clear the screen with the custom gray background color.
        ClearBackground(grey);

        if (gamestate == MAIN_MENU) {
            // Main Menu
            DrawTextEx(font, "WELCOME TO BINARY WARS", { 130, 100 }, 50, 2, WHITE);
            DrawTextEx(font, "1. Start Game", { 300, 200 }, 30, 2, WHITE);
            DrawTextEx(font, "2. Exit", { 300, 250 }, 30, 2, WHITE);

            // Check for user input to navigate the menu.
            if (IsKeyPressed(KEY_ONE)) {
                gamestate = PLAYING; // Transition to the playing state.
                cout << "Game started." << endl;
            }
            if (IsKeyPressed(KEY_TWO)) {
                break; // Exit the game.
            }
        }
        else if (gamestate == PLAYING) {
            // Check if the Tab key is pressed to toggle the paused state.
            if (IsKeyPressed(KEY_TAB)) {
                paused = !paused; // Toggle the paused state.
                cout << "Paused state toggled: " << (paused ? "Paused" : "Running") << endl;
            }
            if (IsKeyPressed(KEY_R)) {
                game.Reset(); // Reset the game state
                cout << "Game reset triggered by pressing R." << endl;
            }
            if (paused) {
                // If the game is paused, display the "Paused" message.
                DrawTextEx(font, "PAUSED", { 330, 325 }, 50, 2, WHITE);
            }
            else {
                // If the game is not paused, update game logic and draw game elements.

                // Handle user input for controlling the game.
                game.HandleInput();
                cout << "Handled input." << endl;

                // Update the game state, including player, enemies, and other elements.
                game.Update();
                cout << "Game state updated." << endl;

                // Check if all lives are gone
                if (game.lives <= 0) {
                    gamestate = GAME_OVER; // Transition to the GAME_OVER state
                    cout << "Game over. Transitioning to GAME_OVER state." << endl;
                }

                // Draw a rounded rectangle border around the game area.
                DrawRectangleRoundedLinesEx({ 10, 10, 780, 780 }, 0.18f, 20, 2, BLUE);

                // Draw a horizontal line at the bottom of the game area.
                DrawLineEx({ 25, 730 }, { 775, 730 }, 3, BLUE);

                // Draw the player's remaining lives as spaceship icons.
                float x = 50.0; // Initial x-coordinate for the first spaceship icon.
                for (int i = 0; i < game.lives; i++) {
                    DrawTextureV(spaceshipImage, { x, 745 }, BLUE); // Draw the spaceship icon.
                    x += 50; // Increment the x-coordinate for the next icon.
                }
                cout << "Lives drawn: " << game.lives << endl;

                // Display the current score.
                DrawTextEx(font, "SCORE", { 50, 15 }, 34, 2, BLUE); // Draw the "SCORE" label.
                string scoreText = FormatWithLeadingZeros(game.score, 5); // Format the score with leading zeros.
                DrawTextEx(font, scoreText.c_str(), { 50, 40 }, 34, 2, BLUE); // Draw the formatted score.

                // Display the high score.
                DrawTextEx(font, "HIGH-SCORE", { 570, 15 }, 34, 2, BLUE); // Draw the "HIGH-SCORE" label.
                string highscoreText = FormatWithLeadingZeros(game.highscore, 5); // Format the high score with leading zeros.
                DrawTextEx(font, highscoreText.c_str(), { 655, 40 }, 34, 2, BLUE); // Draw the formatted high score.

                // Draw all game elements (e.g., aliens, obstacles, lasers) using the Game class.
                game.Draw();
                cout << "Game elements drawn." << endl;
            }
        }
        if (gamestate == GAME_OVER) {
            // Game Over Screen
            DrawTextEx(font, "GAME OVER", { 300, 100 }, 50, 2, WHITE);
            DrawTextEx(font, "1. Return to Main Menu", { 300, 200 }, 30, 2, WHITE);
            DrawTextEx(font, "2. Exit.", { 300, 250 }, 30, 2, WHITE);

            // Check for user input to navigate the game over screen.
            if (IsKeyPressed(KEY_ONE)) {
                game.Reset(); // Reset the game state
                gamestate = MAIN_MENU; // Restart the game
                cout << "Game Menu." << endl;
            }
            if (IsKeyPressed(KEY_TWO)) {
                break; // Exit the game.
            }
        }

        // End drawing the current frame.
        EndDrawing();
        cout << "Frame end." << endl;
    }

    // Close the game window and release resources.
    CloseWindow();
    cout << "Window closed." << endl;

    // Close the audio device and release audio resources.
    CloseAudioDevice();
    cout << "Audio device closed." << endl;

    // Debug: Log program end
    cout << "Program ended." << endl;
}

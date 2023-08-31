// Include necessary headers
#include "GameSession.h"
#include "Entity/Entity.h"
//#include "Grid.h"
// ... Include other necessary headers ...

GameSession::GameSession() : player(nullptr), score(0), highScore(0), currentLevel(1), alarmState(GREEN) {
    // Initialize the grid, player, and other game components
    // Initialize SDL, set up game window, renderer, etc. if not done elsewhere
}

void GameSession::Start() {
    const int FPS = 60;
    const int frameDelay = 1000 / FPS;
    Uint32 frameStart;
    int frameTime;

    // Start the game loop
    while (running) {
        frameStart = SDL_GetTicks();  // Gets the number of milliseconds since SDL library initialization

        Update();
        Render();

        frameTime = SDL_GetTicks() - frameStart;

        if (frameDelay > frameTime) {
            SDL_Delay(frameDelay - frameTime);
        }
    }
    running = true;
}


void GameSession::Update() {
    // Update game logic here

    // Move entities
    MoveEntities();

    // Check collisions
    CheckCollisions();

    // Update game state based on collisions, player actions, etc.
    // Update alarm state, spawn enemies, etc.
}

void GameSession::Render() {
    // Render all game elements to the screen using SDL
    // Draw background, player, enemies, bases, projectiles, HUD elements, etc.

    // First, clear the renderer or the screen
    SDL_RenderClear(renderer);  // Assuming renderer is defined somewhere and initialized

    // Render your game objects here
    // Example:
    // player->Render();
    // for (auto enemy : enemies) enemy->Render();
    // for (auto projectile : projectiles) projectile->Render();

    // Finally, present the renderer
    SDL_RenderPresent(renderer);
}

void GameSession::SetPlayerDirection(Direction dir) {
    switch (dir) {
        case Direction::UP:
            player->SetAngle(0);
            break;
        case Direction::DOWN:
            player->SetAngle(180);
            break;
        case Direction::LEFT:
            player->SetAngle(270);
            break;
        case Direction::RIGHT:
            player->SetAngle(90);
            break;
        case Direction::UP_LEFT:
            player->SetAngle(315);
            break;
        case Direction::UP_RIGHT:
            player->SetAngle(45);
            break;
        case Direction::DOWN_LEFT:
            player->SetAngle(225);
            break;
        case Direction::DOWN_RIGHT:
            player->SetAngle(135);
            break;
        default:
            break;
    }
}

void GameSession::MoveEntities() {
    // Move player, enemies, projectiles, etc.
    // Apply physics, velocity, etc. to relevant entities
}

void GameSession::CheckCollisions() {
    // Use the Grid system or other collision mechanisms to check for collisions

    // Player vs Enemies
    for (auto enemy : enemies) {
        if (player->IsColliding(*enemy)) {
            // Handle player-enemy collision
        }
    }

    // Player projectiles vs Enemies
    for (auto projectile : playerProjectiles) {
        for (auto enemy : enemies) {
            if (projectile->IsColliding(*enemy)) {
                // Handle player projectile-enemy collision
            }
        }
    }

    // Enemy projectiles vs Player
    for (auto projectile : enemyProjectiles) {
        if (player->IsColliding(*projectile)) {
            // Handle enemy projectile-player collision
        }
    }
}

// ... Other GameSession methods ...


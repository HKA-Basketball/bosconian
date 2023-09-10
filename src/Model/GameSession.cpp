// Include necessary headers
#include "GameSession.h"
#include "Entity/Entity.h"
//#include "Grid.h"
// ... Include other necessary headers ...

GameSession::GameSession() : gameMap(nullptr), player(nullptr), score(0), highScore(0), currentLevel(1), alarmState(GREEN) {
    // Initialize the grid, player, and other game components
    // Initialize SDL, set up game window, renderer, etc. if not done elsewhere
}


void GameSession::Update(float deltaTime) {
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
    //SDL_RenderClear(renderer);  // Assuming renderer is defined somewhere and initialized

    // Render your game objects here
    // Example:
    // player->Render();
    // for (auto enemy : enemies) enemy->Render();
    // for (auto projectile : projectiles) projectile->Render();

    // Finally, present the renderer
    //SDL_RenderPresent(renderer);
}

/*void GameSession::SetPlayerDirection(Direction dir) {
    switch (dir) {
        case Direction::UP:
            player->setAngle(0);
            break;
        case Direction::DOWN:
            player->setAngle(180);
            break;
        case Direction::LEFT:
            player->setAngle(270);
            break;
        case Direction::RIGHT:
            player->setAngle(90);
            break;
        case Direction::UP_LEFT:
            player->setAngle(315);
            break;
        case Direction::UP_RIGHT:
            player->setAngle(45);
            break;
        case Direction::DOWN_LEFT:
            player->setAngle(225);
            break;
        case Direction::DOWN_RIGHT:
            player->setAngle(135);
            break;
        default:
            break;
    }
}*/

void GameSession::MoveEntities() {
    // Move player, enemies, projectiles, etc.
    // Apply physics, velocity, etc. to relevant entities
}

void GameSession::CheckCollisions() {
    // Use the Grid system or other collision mechanisms to check for collisions

    // Player vs Enemies
    /*for (auto enemy : enemies) {
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
    }*/
}

// ... Other GameSession methods ...


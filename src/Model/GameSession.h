#ifndef BOSCONIAN_GAMESESSION_H
#define BOSCONIAN_GAMESESSION_H

// Necessary includes, forward declarations, and using statements
#include <vector>

#include "GameMap.h"
#include "Entity/Entity.h"
#include "Entity/Enemy.h"
#include "Entity/Player.h"
#include "Entity/Projectile.h"
#include "../Controller/GameController.h"
// ... Include other necessary headers ...

class GameSession {
public:
    GameSession(int mapWidth, int mapHeight) : gameMap(mapWidth, mapHeight) {}

    GameMap& getGameMap() { return gameMap; }

    // Main game loop function
    void Start();

    // Input, update, and rendering methods
    void Update();
    void Render();

    // Specific gameplay mechanics
    void SetPlayerDirection(Direction dir);
    void MoveEntities();
    void CheckCollisions();
    // ... Add any other necessary methods ...

private:
    bool running;  // Is the game running?
    int score;
    int highScore;
    int currentLevel;

    // Enum to handle alarm states
    enum AlarmState {
        GREEN,
        YELLOW,
        RED
    } alarmState;

    // Game entities (assuming they have been defined elsewhere)
    GameMap gameMap;
    Player* player;   // Assume Player is a subclass of Entity
    std::vector<Enemy*> enemies;
    std::vector<Projectile*> playerProjectiles;
    std::vector<Projectile*> enemyProjectiles;
    // ... Add other game components, like a grid for collision checks ...

    // ... Add other private methods and member variables as needed ...
};

#endif //BOSCONIAN_GAMESESSION_H

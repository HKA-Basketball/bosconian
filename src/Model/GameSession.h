#ifndef BOSCONIAN_GAMESESSION_H
#define BOSCONIAN_GAMESESSION_H

// Necessary includes, forward declarations, and using statements
#include <vector>

#include "GameMap.h"
#include "Entity/Entity.h"
#include "Entity/Enemy.h"
#include "Entity/Player.h"
#include "Entity/Projectile.h"
// ... Include other necessary headers ...

class GameSession {
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
    GameMap* gameMap;
    Player* player;   // Assume Player is a subclass of Entity
    std::vector<Enemy*> enemies;
    std::vector<Enemy*> bases;
    Projectiles* playerProjectiles;
    Projectiles* enemyProjectiles;
    // ... Add other game components, like a grid for collision checks ...

    // ... Add other private methods and member variables as needed ...

public:
    GameSession();

    GameMap* getGameMap() const { return gameMap; }
    Player* getPlayer() const { return player; }

    // Input, update, and rendering methods
    void Update(float deltaTime);
    void Render();

    // Specific gameplay mechanics
    //void SetPlayerDirection(Direction dir);
    void MoveEntities();
    void CheckCollisions();
    // ... Add any other necessary methods ...

};

#endif //BOSCONIAN_GAMESESSION_H

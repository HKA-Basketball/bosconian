#ifndef BOSCONIAN_GAMEMODEL_H
#define BOSCONIAN_GAMEMODEL_H

#include <vector>

#include "Entities/Player.h"
#include "Entities/Obstacle.h"
#include "Entities/Ship.h"
#include "Entities/Base.h"
#include "Camera.h"
#include "World.h"
#include "Background.h"
#include "../Physics/HitboxManager.h"

#include "Level/LevelInfo.h"
#include "Level/LevelManager.h"
#include "Animations/TextAnimation.h"

enum AlertStatus {
    GREEN,
    YELLOW,
    RED
    //FORMATION_ATTACK
};

class GameModel {
    static GameModel* instance;

    Player* player;
    Position* playerPosition{new Position(0, 0)};

    Camera* camera;
    World* world;

    unsigned int score{0};
    unsigned int highscore{0};
    unsigned int lives{3};

    AlertStatus status{GREEN};

    unsigned int round{1};
    LevelInfo levelInfo;
    LevelManager* levelManager;

    TextAnimation* readyAnimation{new TextAnimation("Ready")};
    TextAnimation* gameOverAnimation{new TextAnimation("Game Over")};

    std::vector<Entity*>* enemies = new std::vector<Entity*>();
    std::vector<Base*>* bases = new std::vector<Base*>();

    GameModel() {
        levelManager = new LevelManager();
        world = new World();

        player = new Player({0, 0}, 0);
        camera = Camera::Instance();

        initLevelInfo();

        initEnemies();
    }

    ~GameModel() {
        delete player;
        delete playerPosition;
        delete readyAnimation;
        delete gameOverAnimation;
        for (auto enemy : *enemies) delete enemy;
        for (auto base : *bases) delete base;
        delete enemies;
        delete bases;
    }


public:
    static GameModel* Instance() {
        if (!instance) {
            instance = new GameModel();
            return instance;
        }
        return instance;
    }

    void update(float deltaTime) {
        player->update(deltaTime);
        *playerPosition = player->getPosition();
        camera->centerOn(player->getPosition());

        Background::Instance()->updateStars(deltaTime, camera->getCenter());

        updateProjectiles(player->getProjectiles());
        updateEnemies(deltaTime);
        updateBases(deltaTime);

        clearDeadProjectiles(player->getProjectiles());
        clearDeadEnemies();
        clearDeadBases();
    }

    Player* getPlayer() const {
        return player;
    }

    World* getWorld() const {
        return world;
    }

    Camera* getCamera() const {
        return camera;
    }

    std::vector<Entity*>* getEnemies() {
        return enemies;
    }

    std::vector<Base*>* getBases() {
        return bases;
    }

    unsigned int getScore() const {
        return score;
    };

    unsigned int getHighscore() const {
        return highscore;
    };

    void resetRound() {
        player->reset();
        player->setPosition(levelInfo.playerSpawn);
        camera->centerOn(player->getPosition());
        status = GREEN;
    }

    unsigned int getRound() const {
        return round;
    }

    void nextRound() {
        if(round < UINT32_MAX) {
            round++;
        }
        initLevelInfo();
    }

    void previousRound() {
        if(round > 1) {
            round--;
        }
        initLevelInfo();
    }

    void raiseLives() {
        if(lives < 5) {
            lives++;
        }
    }

    void reduceLives() {
        if(lives > 0) {
            lives--;
        }
    }

    unsigned int getLives() const {
        return lives;
    }

    TextAnimation* getReadyAnimation() const {
        return readyAnimation;
    }

    TextAnimation* getGameOverAnimation() const {
        return gameOverAnimation;
    }

private:

    void initLevelInfo() {
        levelInfo = levelManager->getLevelInfo(round);

        player->setPosition(levelInfo.playerSpawn);
        player->setAngle(0);
        camera->centerOn(player->getPosition());

        for (auto base : *bases) delete base;
        for (Vector2D basePosition : levelInfo.basePositions) {
            bases->push_back(new Base(basePosition, 0, playerPosition));
        }
    }

    void initEnemies() {
        world->markOccupied(levelInfo.playerSpawn, {50, 50});

        for (Base* base : *bases) {
            world->markOccupied(base->getPosition(), base->getTotalSize());
        }

        std::vector<std::vector<Vector2D>> predefinedPositions = world->predefinedPositions();

        // Calculate total number of positions to reserve space efficiently
        size_t totalPositions = 0;
        for (const auto& posSet : predefinedPositions) {
            totalPositions += posSet.size();
        }
        enemies->reserve(enemies->size() + totalPositions);

        int totalUnoccupiedChunks = world->getUnoccupiedChunks().size();
        int shipsToSpawn = 12; // maximum number of ships to spawn
        int shipsPerChunk = shipsToSpawn / totalUnoccupiedChunks; // evenly distribute ships among chunks

        for (const Chunk& chunk : world->getUnoccupiedChunks()) {
            std::vector<Vector2D> positions = predefinedPositions.at(Math::randomInt(0, predefinedPositions.size() - 1));

            int shipsInThisChunk = 0;
            for (Vector2D& position : positions) {
                position.x += chunk.x;
                position.y += chunk.y;

                if (shipsInThisChunk < shipsPerChunk || Math::randomFloat(0.0f, 1.0f) > 0.20f) {
                    enemies->push_back(new Obstacle(position, Math::randomFloat(0, 359)));
                } else {
                    enemies->push_back(new Ship(position, Math::randomFloat(0, 359), playerPosition));
                    shipsInThisChunk++;
                }
            }
        }
    }

    void haveProjectilesHitPlayer(Projectiles* projectiles) {
        for (Projectile* projectile : *projectiles) {
            hasProjectileHitEntity(projectile, player);
        }
    }

    void hasEntityHitPlayer(Entity* entity) {
        hasEntityHitEntity(entity, player);
    }

    void haveProjectilesHitEntity(Projectiles* projectiles, Entity* entity) {
        for (Projectile* projectile : *projectiles) {
            hasProjectileHitEntity(projectile, entity);
        }
    }

    void hasProjectileHitEntity(Projectile* projectile, Entity* entity) {
        if (HitboxManager::areColliding(projectile->getHitbox(), entity->getHitbox())) {
            if (!projectile->isDefeated()) {
                projectile->setDefeated();
            }
            if (!entity->isDefeated()) {
                entity->setDefeated();
            }
        }
    }

    void hasEntityHitEntity(Entity* entityHitting, Entity* entityHit) {
        if (HitboxManager::areColliding(entityHit->getHitbox(), entityHitting->getHitbox())) {
            if (!entityHit->isDefeated()) {
                entityHit->setDefeated();
            }
        }
    }

    void updateProjectiles(Projectiles* projectiles) {
        for (Projectile* projectile : *projectiles) {
            if (!Camera::Instance()->IsInView(*projectile)) {
                projectile->setDefeated();
            }
        }
    }

    void updateEnemies(float deltaTime) {
        for (Entity* enemy : *enemies) {
            enemy->update(deltaTime);
            haveProjectilesHitEntity(player->getProjectiles(), enemy);
            hasEntityHitPlayer(enemy);

            if(enemy->isDefeated()) {
                score += enemy->receivePoints();
            }
        }
    }

    void updateBases(float deltaTime) {
        for (Base* base : *bases) {
            base->update(deltaTime);

            haveProjectilesHitEntity(player->getProjectiles(), base);
            hasEntityHitPlayer(base);

            if(base->isDefeated()) {
                score += base->receivePoints();
            }

            for (Cannon* cannon : *base->getCannons()) {
                updateProjectiles(cannon->getProjectiles());

                haveProjectilesHitEntity(player->getProjectiles(), cannon);
                hasEntityHitPlayer(cannon);
                haveProjectilesHitPlayer(cannon->getProjectiles());

                if(cannon->isDefeated()) {
                    score += cannon->receivePoints();
                }
            }
        }
    }

    void clearDeadProjectiles(Projectiles* projectiles) {
        for (auto it = projectiles->begin(); it != projectiles->end(); ) {
            if ((*it)->isDead()) {
                delete *it;
                it = projectiles->erase(it);
            } else {
                ++it;
            }
        }
    }

    void clearDeadEnemies() {
        for (auto it = enemies->begin(); it != enemies->end(); ) {
            if ((*it)->isDead()) {
                delete *it;
                it = enemies->erase(it);
            } else {
                ++it;
            }
        }
    }

    void clearDeadBases() {
        for (auto it = bases->begin(); it != bases->end(); ) {
            if ((*it)->isDead()) {
                delete *it;
                it = bases->erase(it);
            } else {
                for (Cannon* cannon : *(*it)->getCannons()) {
                    clearDeadProjectiles(cannon->getProjectiles());
                }
                ++it;
            }
        }
    }

};

#endif //BOSCONIAN_GAMEMODEL_H

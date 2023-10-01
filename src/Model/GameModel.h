#ifndef BOSCONIAN_GAMEMODEL_H
#define BOSCONIAN_GAMEMODEL_H

#include <vector>

#include "Entities/Player.h"
#include "Entities/Obstacle.h"
#include "Entities/Ship.h"
#include "Entities/Base.h"
#include "Camera.h"
#include "World.h"
#include "../View/Background.h"
#include "../Physics/HitboxManager.h"

#include "Level/LevelInfo.h"
#include "Level/LevelManager.h"

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

    unsigned int score{0};
    unsigned int highscore{0};
    unsigned int lives{3};

    AlertStatus status{GREEN};

    unsigned int round{1};
    LevelInfo levelInfo;
    LevelManager* levelManager;

    std::vector<Entity*>* enemies = new std::vector<Entity*>();
    std::vector<Base*>* bases = new std::vector<Base*>();

    GameModel() {
        levelManager = new LevelManager();
        levelInfo = levelManager->getLevelInfo(round);

        player = new Player(levelInfo.playerSpawn, 0);

        enemies->push_back(new Obstacle({1600, 1600}, 0));
        enemies->push_back(new Obstacle({5, 5}, 45));
        enemies->push_back(new Ship({1350, 1350}, 0, playerPosition));

        for (Vector2D basePosition : levelInfo.basePositions) {
            bases->push_back(new Base(basePosition, 0, playerPosition));
        }

        //bases->push_back(new Base({1050, 1750}, 0, playerPosition));
        //bases->push_back(new Base({2500, 1500}, 0, playerPosition));
    }

    ~GameModel() {
        delete player;
        delete playerPosition;
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

        Camera* camera = Camera::Instance();
        camera->centerOn(player->getPosition());

        Background::Instance()->updateStars(deltaTime, camera->getCenter());

        updateProjectiles(player->getProjectiles());

        for (auto it = enemies->begin(); it != enemies->end(); ) {
            Entity* enemy = *it;
            enemy->update(deltaTime);
            checkforCollision(enemy, player->getProjectiles());

            if(enemy->isDefeated()) {
                score += enemy->receivePoints();
            }

            if (enemy->isDead()) {
                delete *it;
                it = enemies->erase(it);
            } else {
                ++it;
            }
        }

        for (auto it = bases->begin(); it != bases->end(); ) {
            Base* base = *it;
            base->update(deltaTime);
            checkforCollision(base, player->getProjectiles());

            if(base->isDefeated()) {
                score += base->receivePoints();
            }

            for (Cannon* cannon : *base->getCannons()) {
                updateProjectiles(cannon->getProjectiles());
                checkforCollision(cannon, player->getProjectiles());

                if(cannon->isDefeated()) {
                    score += cannon->receivePoints();
                }
            }

            if (base->isDead()) {
                delete *it;
                it = bases->erase(it);
            } else {
                ++it;
            }
        }

    }

    Player* getPlayer() {
        return player;
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

private:

    void updateProjectiles(Projectiles* projectiles) {
        //auto& projectiles = *p;
        for (auto it = projectiles->begin(); it != projectiles->end(); /* no increment here */) {
            Projectile* projectile = *it;
            if (!Camera::Instance()->IsInView(*projectile)) {
                it = projectiles->erase(it); // erase returns the iterator pointing to the next element
            } else {
                ++it;
            }
        }
    }
    void checkforCollision(Entity* entity, Projectiles* projectiles) {
        bool entityCollisionDetected = false;
        auto projectileIt = projectiles->begin();

        while (projectileIt != projectiles->end()) {
            if (HitboxManager::areColliding(entity->getHitbox(), (*projectileIt)->getHitbox())) {
                entityCollisionDetected = true;

                // Free memory if needed, e.g., if using raw pointers
                delete *projectileIt;

                // Erase the collided projectile and update the iterator
                projectileIt = projectiles->erase(projectileIt);
            } else {
                ++projectileIt;
            }
        }

        if (entityCollisionDetected) {
            if (!entity->isDefeated()) {
                entity->setDefeated();
            }
        }
    }

};

#endif //BOSCONIAN_GAMEMODEL_H

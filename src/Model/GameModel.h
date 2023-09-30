#ifndef BOSCONIAN_GAMEMODEL_H
#define BOSCONIAN_GAMEMODEL_H

#include <vector>

#include "Entities/Player.h"
#include "Entities/Obstacle.h"
#include "Entities/Enemy.h"
#include "Entities/Base.h"
#include "Camera.h"
#include "World.h"
#include "../View/Background.h"

enum AlertStatus {
    GREEN,
    YELLOW,
    RED
    //FORMATION_ATTACK
};

class GameModel {
    static GameModel* instance;

    Player* player;

    unsigned int points{0};
    unsigned int highScore{0};
    unsigned int lives{3};

    AlertStatus status{GREEN};

    std::vector<Enemy*>* enemies = new std::vector<Enemy*>();
    std::vector<Obstacle*>* obstacles = new std::vector<Obstacle*>();
    std::vector<Base*>* bases = new std::vector<Base*>();

    GameModel() {
        player = new Player({1500, 1500}, 0);
        obstacles->push_back(new Obstacle({1600, 1600}, 0));
        obstacles->push_back(new Obstacle({5, 5}, 45));
        enemies->push_back(new Enemy({1350, 1350}, 0));
        bases->push_back(new Base({1050, 1750}, 0));
        bases->push_back(new Base({2350, 1500}, 0));
    }

    ~GameModel() {
        delete player;
        for (auto enemy : *enemies) delete enemy;
        for (auto obstacle : *obstacles) delete obstacle;
        for (auto base : *bases) delete base;
        delete enemies;
        delete obstacles;
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

        Camera* camera = Camera::Instance();
        camera->centerOn(player->getPosition());

        Background::Instance()->updateStars(deltaTime, camera->getCenter());

        updateProjectiles(player->getProjectiles());

        for (Enemy* enemy : *enemies) {
            enemy->updatePlayerPosition(player->getWrappedPositions());
            enemy->update(deltaTime);
        }

        for (Obstacle* obstacle : *obstacles) {
            obstacle->update(deltaTime);
        }

        for (Base* base : *bases) {
            base->updatePlayerPosition(player->getPosition());
            base->update(deltaTime);

            for (Cannon* cannon : *base->getCannons()) {
                updateProjectiles(cannon->getProjectiles());
            }
        }

    }

    Player* getPlayer() {
        return player;
    }

    std::vector<Enemy*>* getEnemies() {
        return enemies;
    }

    std::vector<Obstacle*>* getObstacles() {
        return obstacles;
    }

    std::vector<Base*>* getBases() {
        return bases;
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

};

#endif //BOSCONIAN_GAMEMODEL_H

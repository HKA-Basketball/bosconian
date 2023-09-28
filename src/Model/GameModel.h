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
        enemies->push_back(new Enemy({1350, 1350}, 0));
        bases->push_back(new Base({1250, 1750}, 0));
    }

    ~GameModel() {
        delete player;

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

        for (Projectile* projectile : *player->getProjectiles()) {
            //projectile->setPosition(World::WrapPosition(projectile->getPosition()));
            //camera->IsInView()
        }

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

};

#endif //BOSCONIAN_GAMEMODEL_H

#ifndef BOSCONIAN_GAMEMODEL_H
#define BOSCONIAN_GAMEMODEL_H

#include <vector>

#include "../Physics/HitboxManager.h"
#include "../Sound/SoundEngine.h"

#include "Camera.h"
#include "World.h"
#include "Background.h"
#include "Level/LevelInfo.h"
#include "Level/LevelManager.h"

#include "Entities/Player.h"
#include "Entities/Obstacle.h"
#include "Entities/Ship.h"
#include "Entities/Base.h"

#include "Animations/TextAnimation.h"
#include "../Utilities/Random.h"
#include "../Utilities/Settings.h"
#include "../Utilities/IniLike.h"

enum Condition {
    GREEN,
    YELLOW,
    RED,
    FORMATION_ATTACK
};

class GameModel {
protected:
    SoundEngine* soundEngine;

    Player* player;
    Position* playerPosition{new Position(0, 0)};

    Camera* camera;
    Background* background;
    World* world;

    unsigned int score{0};
    unsigned int highscore{0};

    unsigned int nextLive{0};
    unsigned int lives{Settings::Instance()->getStartLives()};

    Condition condition{Condition::GREEN};

    unsigned int round{1};
    LevelInfo levelInfo;
    LevelManager* levelManager;

    TextAnimation* readyAnimation{new TextAnimation("Ready")};
    TextAnimation* gameOverAnimation{new TextAnimation("Game Over")};
    TextAnimation* roundClearAnimation{new TextAnimation("Round Clear")};

    std::vector<Entity*>* enemies = new std::vector<Entity*>();
    std::vector<Base*>* bases = new std::vector<Base*>();

    Spy* activeSpy;

public:
    GameModel(SoundEngine* soundEngine) {
        this->soundEngine = soundEngine;

        levelManager = new LevelManager();
        if (Settings::Instance()->getCustomLevelMode()) {
            IniLike levelConfig(".\\cfg\\level.ini");
            std::vector<LevelInfo> tmpLevelInfoList;
            levelConfig.add_item("Levels", "levels", tmpLevelInfoList);
            levelConfig.read();
            levelManager->updateLevels(tmpLevelInfoList);
        } else {
            levelManager->updateLevels(levelInfoListDef);
        }

        world = new World();
        background = new Background();
        camera = new Camera();

        player = new Player({0, 0}, 0);

        initLevel();
        initBonusFighter();
    }

    ~GameModel() {
        delete levelManager;
        delete world;
        delete background;
        delete player;
        delete camera;
        delete playerPosition;
        delete readyAnimation;
        delete gameOverAnimation;
        for (auto enemy : *enemies) delete enemy;
        for (auto base : *bases) delete base;
        delete enemies;
        delete bases;
    }

    virtual void update(float deltaTime) {
        player->update(deltaTime);
        *playerPosition = player->getPosition();
        camera->centerOn(player->getPosition());

        background->update(deltaTime);

        updateProjectiles(player->getProjectiles());
        updateEnemies(deltaTime);
        updateBases(deltaTime);

        updateCondition();
        updateBonusFighter();

        clearDeadProjectiles(player->getProjectiles());
        clearDeadEnemies();
        clearDeadBases();
    }

    void resetRound() {
        player->reset();
        player->setPosition(levelInfo.playerSpawn);
        player->setAngle(0);
        camera->centerOn(player->getPosition());
        condition = Condition::GREEN;
        for (Base* base : *bases) base->resetProjectiles();
    }

    void nextRound() {
        if(round < UINT32_MAX) {
            round++;
        }
        initLevel();
    }

    void previousRound() {
        if(round > 1) {
            round--;
        }
        initLevel();
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

    Player* getPlayer() const {
        return player;
    }

    std::vector<Entity*>* getEnemies() {
        return enemies;
    }

    std::vector<Base*>* getBases() {
        return bases;
    }

    Spy* getSpy() {
        return activeSpy;
    }

    World* getWorld() const {
        return world;
    }

    Camera* getCamera() const {
        return camera;
    }

    Background* getBackground() const {
        return background;
    }

    TextAnimation* getReadyAnimation() const {
        return readyAnimation;
    }

    TextAnimation* getGameOverAnimation() const {
        return gameOverAnimation;
    }

    TextAnimation* getRoundClearAnimation() const {
        return roundClearAnimation;
    }

    unsigned int getRound() const {
        return round;
    }

    Condition getCondition() const {
        return condition;
    }

    unsigned int getScore() const {
        return score;
    };

    unsigned int getHighscore() const {
        return highscore;
    };

    unsigned int getLives() const {
        return lives;
    }

protected:

    virtual void initLevel() {
        levelInfo = levelManager->getLevelInfo(round);
        resetRound();

        for (auto base : *bases) delete base;
        bases->clear();
        for (const Vector2D& basePosition : levelInfo.basePositions) {
            Degree baseAngle = Random::getRandomOne(0, 90);
            bases->push_back(new Base(basePosition, baseAngle, playerPosition));
        }

        if (bases->size() > 0) {
            activeSpy = bases->at(Random::randomInt(0, bases->size() - 1))->getSpy();
            activeSpy->searchForPlayer();
        }

        spawnEnemies();
    }

    void spawnEnemies() {
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

        for (auto enemy : *enemies) delete enemy;
        enemies->clear();
        enemies->reserve(enemies->size() + totalPositions);

        int totalUnoccupiedChunks = world->getUnoccupiedChunks().size();
        int shipsToSpawn = 12; // maximum number of ships to spawn
        int shipsPerChunk = shipsToSpawn / totalUnoccupiedChunks; // evenly distribute ships among chunks

        for (const Chunk& chunk : world->getUnoccupiedChunks()) {
            std::vector<Vector2D> positions = predefinedPositions.at(Random::randomInt(0, predefinedPositions.size() - 1));

            int shipsInThisChunk = 0;
            for (Vector2D& position : positions) {
                position.x += chunk.x;
                position.y += chunk.y;

                if (shipsInThisChunk < shipsPerChunk || Random::randomFloat(0.0f, 1.0f) > 0.20f) {
                    enemies->push_back(new Obstacle(position, Random::randomFloat(0, 359)));
                } else {
                    enemies->push_back(new Ship(position, Random::randomFloat(0, 359), playerPosition));
                    shipsInThisChunk++;
                }
            }
        }
    }
    void initBonusFighter() {
        BonusFighter bonusFighter = Settings::Instance()->getBonusFighter();

        switch (bonusFighter) {
            default:
                break;
            case BonusFighter::Opt0_0:
                nextLive = 10000;
                break;
            case BonusFighter::Opt0_1:
            case BonusFighter::Opt0_2:
            case BonusFighter::Opt0_3:
            case BonusFighter::Opt1_0:
                nextLive = 15000;
                break;
            case BonusFighter::Opt0_4:
            case BonusFighter::Opt0_5:
            case BonusFighter::Opt1_1:
            case BonusFighter::Opt1_2:
                nextLive = 20000;
                break;
            case BonusFighter::Opt0_6:
            case BonusFighter::Opt1_3:
            case BonusFighter::Opt1_4:
            case BonusFighter::Opt1_5:
            case BonusFighter::Opt1_6:
                nextLive = 30000;
                break;
        }
    }

    void updateBonusFighter() {
        BonusFighter bonusFighter = Settings::Instance()->getBonusFighter();

        if (score < nextLive || bonusFighter == BonusFighter::None || nextLive == UINT32_MAX) {
            return;

        } else {
            raiseLives();
        }

        switch (bonusFighter) {
            default:
                break;
            case BonusFighter::Opt0_0:
                nextLive = nextLive == 10000 ? 50000 : nextLive;
                nextLive = nextLive >= 50000 ? nextLive + 50000 : nextLive;
                break;
            case BonusFighter::Opt0_1:
                nextLive = nextLive == 15000 ? 50000 : nextLive;
                nextLive = nextLive == 50000 ? UINT32_MAX : nextLive;
            case BonusFighter::Opt0_2:
                nextLive = nextLive == 15000 ? 50000 : nextLive;
                nextLive = nextLive >= 50000 ? nextLive + 50000 : nextLive;
            case BonusFighter::Opt0_3:
                nextLive = nextLive == 15000 ? 70000 : nextLive;
                nextLive = nextLive >= 70000 ? nextLive + 70000 : nextLive;
            case BonusFighter::Opt0_4:
                nextLive = nextLive == 20000 ? 70000 : nextLive;
                nextLive = nextLive == 70000 ? UINT32_MAX : nextLive;
            case BonusFighter::Opt0_5:
                nextLive = nextLive == 20000 ? 70000 : nextLive;
                nextLive = nextLive >= 70000 ? nextLive + 70000 : nextLive;
            case BonusFighter::Opt0_6:
                nextLive = nextLive == 30000 ? 100000 : nextLive;
                nextLive = nextLive >= 100000 ? nextLive + 100000 : nextLive;
                break;
            case BonusFighter::Opt1_0:
                nextLive = nextLive == 15000 ? 70000 : nextLive;
                nextLive = nextLive == 70000 ? UINT32_MAX : nextLive;
                break;
            case BonusFighter::Opt1_1:
                nextLive = nextLive == 20000 ? 100000 : nextLive;
                nextLive = nextLive == 100000 ? UINT32_MAX : nextLive;
                break;
            case BonusFighter::Opt1_2:
                nextLive = nextLive == 20000 ? 70000 : nextLive;
                nextLive = nextLive == 70000 ? UINT32_MAX : nextLive;
                break;
            case BonusFighter::Opt1_3:
                nextLive = nextLive == 30000 ? 120000 : nextLive;
                nextLive = nextLive == 120000 ? UINT32_MAX : nextLive;
                break;
            case BonusFighter::Opt1_4:
                nextLive = nextLive == 30000 ? 100000 : nextLive;
                nextLive = nextLive >= 100000 ? nextLive + 100000 : nextLive;
                break;
            case BonusFighter::Opt1_5:
                nextLive = nextLive == 30000 ? 120000 : nextLive;
                nextLive = nextLive >= 120000 ? nextLive + 120000 : nextLive;
                break;
            case BonusFighter::Opt1_6:
                nextLive = nextLive == 30000 ? 80000 : nextLive;
                nextLive = nextLive >= 80000 ? nextLive + 80000 : nextLive;
                break;
        }

    }

    void haveProjectilesHitPlayer(Projectiles* projectiles) {
        for (Projectile* projectile : *projectiles) {
            hasProjectileHitEntity(projectile, player);
        }
    }

    void hasEntityHitPlayer(Entity* entity) {
        if (HitboxManager::areColliding(entity->getHitbox(), player->getHitbox())) {
            if (!player->isDefeated()) {
                player->setDefeated();
                soundEngine->playSoundEffect("sounds/explode.wav");
                soundEngine->playSoundEffect("sounds/game_over.wav");
            }
        }
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
                soundEngine->playSoundEffect("sounds/explode.wav");
            }
        }
    }

    void hasEntityHitEntity(Entity* entityHitting, Entity* entityHit) {
        if (HitboxManager::areColliding(entityHit->getHitbox(), entityHitting->getHitbox())) {
            if (!entityHit->isDefeated()) {
                entityHit->setDefeated();
                soundEngine->playSoundEffect("sounds/explode.wav");
            }
        }
    }

    void updateProjectiles(Projectiles* projectiles) {
        for (Projectile* projectile : *projectiles) {
            if (!camera->IsInView(*projectile)) {
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

    virtual void updateBases(float deltaTime) {
        for (Base* base : *bases) {
            base->update(deltaTime);

            haveProjectilesHitEntity(player->getProjectiles(), base);
            hasEntityHitPlayer(base);

            if(base->isDefeated()) {
                score += base->receivePoints();
            }

            updateSpy(base->getSpy());

            for (Cannon* cannon : *base->getCannons()) {
                updateCannon(cannon);
            }
        }
    }

    void updateCannon(Cannon* cannon) {
        updateProjectiles(cannon->getProjectiles());

        haveProjectilesHitEntity(player->getProjectiles(), cannon);
        hasEntityHitPlayer(cannon);
        haveProjectilesHitPlayer(cannon->getProjectiles());

        if(cannon->isDefeated()) {
            score += cannon->receivePoints();
        }
    }

    void updateSpy(Spy* spy) {
        const float elapsedTime{0.f};
        const float length{3.f};

        haveProjectilesHitEntity(player->getProjectiles(), spy);
        hasEntityHitPlayer(spy);

        if(activeSpy->isDefeated()) {
            score = activeSpy->receivePoints();
        }
    }

    void updateCondition() {
        auto defeated = activeSpy->isDefeated();
        auto returning = activeSpy->isReturningToBase();
        auto returned = activeSpy->returnedToBase();

        if(defeated) {
            condition = Condition::GREEN;

        } else if (returning) {
            condition = Condition::YELLOW;

        } else if (returned) {
            condition = Condition::RED;
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

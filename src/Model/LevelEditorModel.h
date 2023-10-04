#ifndef BOSCONIAN_LEVELEDITORMODEL_H
#define BOSCONIAN_LEVELEDITORMODEL_H

#include "Level/LevelInfo.h"
#include "GameModel.h"
#include "../Utilities/IniLike.h"
#include <algorithm>

class LevelEditorModel : public GameModel {
    IniLike levelConfig;
    std::vector<LevelInfo> levelInfos;

public:
    explicit LevelEditorModel(SoundEngine* soundEngine, const std::string& configFile = ".\\cfg\\level.ini")
    : GameModel(soundEngine), levelConfig(configFile), levelInfos(levelInfoList) {
        levelConfig.add_item("Levels", "levels", levelInfos);
    }

    void update(float deltaTime) override {
        *playerPosition = player->getPosition();
        camera->centerOn(player->getPosition());

        background->update(deltaTime);
    }

    void updateLevel() {
        initLevel();
    }

    int getCurrentLevel() {
        return levelInfo.levelNumber;
    }

    void increaseLevel() {
        levelInfo = levelManager->getLevelInfoByLevel(getCurrentLevel() + 1);
    }

    void decreaseLevel() {
        levelInfo = levelManager->getLevelInfoByLevel(getCurrentLevel() - 1);
    }

    void saveLevels() {
        levelConfig.write();
        levelConfig.read();
    }

    void readLevels() {
        levelConfig.read();
    }

    void placeBase(int lvl, const Vector2D& pos) {
        for (auto& l : levelInfos) {
            if (l.levelNumber == lvl) {
                for (Base* base : *bases) {
                    Hitbox currentHitbox(base->getPosition()-(base->getTotalSize()/2), base->getTotalSize());
                    Hitbox newHitbox(pos-(base->getTotalSize()/2), base->getTotalSize());
                    if (HitboxManager::areColliding(currentHitbox, newHitbox)) {
                        return;
                    }
                }

                l.basePositions.push_back(pos);
                return;
            }
        }
    }

    void setPlayerSpawnPos(int lvl, const Vector2D& pos) {
        for (auto& l : levelInfos) {
            if (l.levelNumber == lvl) {
                l.playerSpawn = pos;
                return;
            }
        }
    }

    void undoBase(int lvl) {
        for (auto& l : levelInfos) {
            if (l.levelNumber == lvl) {
                for (Base* base : *bases) {
                    Hitbox currentHitbox(base->getPosition()-(base->getTotalSize()/2), base->getTotalSize());
                    if (HitboxManager::areColliding(currentHitbox, player->getHitbox())) {
                        auto it = std::find(l.basePositions.begin(), l.basePositions.end(), base->getPosition());
                        if (it != l.basePositions.end()) {
                            l.basePositions.erase(it);
                            return;
                        }
                    }
                }
            }
        }
    }

private:
    void updateBases(float deltaTime) override {
        for (Base* base : *bases) {
            base->update(deltaTime);
        }
    }

    void initLevel() override {
        levelManager->updateLevels(levelInfos);
        levelInfo = levelManager->getLevelInfoByLevel(levelInfo.levelNumber);

        for (auto base : *bases) delete base;
        bases->clear();
        for (const Vector2D& basePosition : levelInfo.basePositions) {
            Degree baseAngle = Random::getRandomOne(0, 90);
            bases->push_back(new Base(basePosition, baseAngle, playerPosition));
        }
    }
};


#endif //BOSCONIAN_LEVELEDITORMODEL_H

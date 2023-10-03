#ifndef BOSCONIAN_LEVELEDITORMODEL_H
#define BOSCONIAN_LEVELEDITORMODEL_H

#include "Level/LevelInfo.h"
#include "GameModel.h"
#include "../Utilities/IniLike.h"

class LevelEditorModel : public GameModel {
    static LevelEditorModel* instance;
    IniLike levelConfig;

    explicit LevelEditorModel(const std::string& configFile = ".\\cfg\\level.ini") : GameModel(), levelConfig(configFile) {
        levelConfig.add_item("Levels", "levels", levelInfoList);
    }
public:
    static LevelEditorModel* Instance() {
        if (!instance) {
            instance = new LevelEditorModel();
            return instance;
        }
        return instance;
    }

    void update(float deltaTime) override {
        *playerPosition = player->getPosition();
        camera->centerOn(player->getPosition());

        background->update(deltaTime);

        updateBases(deltaTime);
        clearDeadBases();
    }

    int getCurrentLevel() {
        return levelInfo.levelNumber;
    }

    void increaseLevel() {
        levelManager->getLevelInfoByLevel(levelInfo.levelNumber + 1);
    }

    void decreaseLevel() {
        levelManager->getLevelInfoByLevel(levelInfo.levelNumber - 1);
    }

    void saveLevels() {
        levelConfig.write();
        levelConfig.read();
    }

    void readLevels() {
        levelConfig.read();
    }

    void placeBase(int lvl, const Vector2D& pos) {
        for (auto& l : levelInfoList) {
            if (l.levelNumber == lvl) {
                l.basePositions.push_back(pos);
                return;
            }
        }
    }

    void setPlayerSpawnPos(int lvl, const Vector2D& pos) {
        for (auto& l : levelInfoList) {
            if (l.levelNumber == lvl) {
                l.playerSpawn = pos;
                return;
            }
        }
    }

    void undoBase(int lvl) {
        for (auto& l : levelInfoList) {
            if (l.levelNumber == lvl) {
                l.basePositions.pop_back();
                return;
            }
        }
    }

private:
    void updateBases(float deltaTime) override {
        for (Base* base : *bases) {
            base->update(deltaTime);
        }
    }

};


#endif //BOSCONIAN_LEVELEDITORMODEL_H

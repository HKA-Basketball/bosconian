#ifndef BOSCONIAN_LEVELEDITORMODEL_H
#define BOSCONIAN_LEVELEDITORMODEL_H

#include "GameModel.h"
#include "../Utilities/IniLike.h"

class LevelEditorModel : public GameModel {
    IniLike levelConfig;

public:
    explicit LevelEditorModel(const std::string& configFile = ".\\cfg\\level.ini") : GameModel(), levelConfig(configFile) {
        levelConfig.add_item("Levels", "levels", levelInfoList);
    }

    void update(float deltaTime) override {
        player->update(deltaTime);
        *playerPosition = player->getPosition();
        camera->centerOn(player->getPosition());

        background->update(deltaTime);
    }

    void saveLevels() {
        levelConfig.write();
        levelConfig.read();
    }

    void readLevels() {
        levelConfig.read();
    }

    static void placeBase(int lvl, const Vector2D& pos) {
        for (auto& l : levelInfoList) {
            if (l.levelNumber == lvl) {
                l.basePositions.push_back(pos);
                return;
            }
        }
    }

    static void setPlayerSpawnPos(int lvl, const Vector2D& pos) {
        for (auto& l : levelInfoList) {
            if (l.levelNumber == lvl) {
                l.playerSpawn = pos;
                return;
            }
        }
    }

    static void undoBase(int lvl) {
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

#ifndef BOSCONIAN_LEVELMANAGER_H
#define BOSCONIAN_LEVELMANAGER_H

#include "../../includes.h"
#include "../Utilities/GlobalVars.h"

namespace Game {

    class LevelManager {
    private:
        std::vector<Utils::Level> lvlsInfos;
        int currentRound;
        int currentLevel;

    public:
        LevelManager(std::vector<Utils::Level>& levels) {
            lvlsInfos = levels;
            currentRound = 1;
            currentLevel = 1;
            LOG("Round " + std::to_string(currentRound) + " - Selected Level: " + std::to_string(currentLevel));
        }

        void selectLevel(int round) {
            currentRound = round;

            if (round < 12) {
                currentLevel = round;
            } else {
                int sequenceIndex = (round - 12) % 6;
                int sequenceLevels[] = {3, 4, 12, 13, 5, 14};
                currentLevel = sequenceLevels[sequenceIndex];
            }

            LOG("Round " + std::to_string(round) + " - Selected Level: " + std::to_string(currentLevel));
        }

        void increaseRound() {
            selectLevel(currentRound+1);
        }

        Utils::Vector2D getPlayerSpawnLocation() {
            return lvlsInfos[currentLevel - 1].playerPos;
        }

        std::vector<Utils::Vector2D> getBaseShipsSpawnLocations() {
            return lvlsInfos[currentLevel - 1].baseShipsPos;
        }
    };

} // Game

#endif //BOSCONIAN_LEVELMANAGER_H

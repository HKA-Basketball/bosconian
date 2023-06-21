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

        void selectLevel(int round);

        int getCurrentLevel() const;

        void updateLevels(std::vector<Utils::Level>& levels);

        void increaseLevel();

        void decreaseLevel();

        void increaseRound();

        Utils::Vector2D getPlayerSpawnLocation();

        std::vector<Utils::Vector2D> getBaseShipsSpawnLocations();
    };

} // Game

#endif //BOSCONIAN_LEVELMANAGER_H

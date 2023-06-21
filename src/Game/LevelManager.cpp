#include "LevelManager.h"

namespace Game {

    void LevelManager::selectLevel(int round) {
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

    int LevelManager::getCurrentLevel() const {
        return currentLevel;
    }

    void LevelManager::updateLevels(std::vector<Utils::Level>& levels) {
        lvlsInfos = levels;
    }

    void LevelManager::increaseLevel() {
        if (currentLevel < 14) {
            currentLevel++;
        }
        else {
            currentLevel = 1;
        }
        LOG("Selected Level: " + std::to_string(currentLevel));
    }

    void LevelManager::decreaseLevel() {
        if (currentLevel > 1) {
            currentLevel--;
        }
        else {
            currentLevel = 14;
        }
        LOG("Selected Level: " + std::to_string(currentLevel));
    }

    void LevelManager::increaseRound() {
        selectLevel(currentRound+1);
    }

    Utils::Vector2D LevelManager::getPlayerSpawnLocation() {
        return lvlsInfos[currentLevel - 1].playerPos;
    }

    std::vector<Utils::Vector2D> LevelManager::getBaseShipsSpawnLocations() {
        return lvlsInfos[currentLevel - 1].baseShipsPos;
    }
} // Game
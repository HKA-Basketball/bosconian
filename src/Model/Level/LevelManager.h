#ifndef BOSCONIAN_LEVELMANAGER_H
#define BOSCONIAN_LEVELMANAGER_H

#include <vector>

#include "LevelInfo.h"

class LevelManager {
private:
    const std::vector<LevelInfo> levels;
    const std::vector<int> repeatSequence = {3, 4, 12, 13, 5, 14};

public:
    LevelManager() : LevelManager(levelInfoList) {}
    LevelManager(const std::vector<LevelInfo>& levels) : levels(levels) {}

    const LevelInfo& getLevelInfo(int round) const {
        // If round is between 1 and 11, return corresponding level
        if(round >= 1 && round <= 11) {
            return levels[round - 1]; // Adjusting for 0-based indexing
        }

        // For rounds beyond 11, get the level from the repeated sequence
        int repeatRound = (round - 12) % repeatSequence.size();
        return levels[repeatSequence[repeatRound] - 1]; // Adjusting for 0-based indexing
    }

    const LevelInfo& getLevelInfoByLevel(int level) const {
        if(level >= 1 && level <= 14) {
            return levels[level - 1]; // Adjusting for 0-based indexing
        }
        return levels[0];
    }
};

// Usage:
// LevelManager manager(levels);
// auto levelInfoForRound20 = manager.getLevelInfo(20);

#endif //BOSCONIAN_LEVELMANAGER_H

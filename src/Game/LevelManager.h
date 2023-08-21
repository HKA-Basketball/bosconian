#ifndef BOSCONIAN_LEVELMANAGER_H
#define BOSCONIAN_LEVELMANAGER_H

#include "../../includes.h"
#include "../Utilities/GlobalVars.h"

namespace Game {

    /**
     * The LevelManager class is responsible for managing game levels and rounds.
     */
    class LevelManager {
    private:
        std::vector<Utils::Level> lvlsInfos;
        /** The current round number. */
        int currentRound;
        /** The current level number within the round. */
        int currentLevel;

    public:
        /**
         * Constructs a LevelManager instance with the specified list of levels.
         * \param levels The list of level information objects.
         */
        LevelManager(std::vector<Utils::Level>& levels) {
            lvlsInfos = levels;
            currentRound = 1;
            currentLevel = 1;
            LOG("Round " + std::to_string(currentRound) + " - Selected Level: " + std::to_string(currentLevel));
        }

        /**
         * Selects a level for the specified round.
         * \param round The round number.
         */
        void selectLevel(int round);

        /**
         * Gets the current level number within the round.
         * \return The current level number.
         */
        int getCurrentLevel() const;

        /**
         * Updates the list of levels.
         * \param levels The updated list of level information objects.
         */
        void updateLevels(std::vector<Utils::Level>& levels);

        /**
         * Increases the current level number.
         */
        void increaseLevel();

        /**
         * Decreases the current level number.
         */
        void decreaseLevel();

        /**
         * Increases the current round number.
         */
        void increaseRound();

        /**
         * Retrieves the player's spawn location for the current level.
         * \return The player's spawn location as a Vector2D.
         */
        Utils::Vector2D getPlayerSpawnLocation();

        /**
         * Retrieves the spawn locations of base ships for the current level.
         * \return The list of base ship spawn locations as Vector2D objects.
         */
        std::vector<Utils::Vector2D> getBaseShipsSpawnLocations();
    };

} // Game

#endif //BOSCONIAN_LEVELMANAGER_H

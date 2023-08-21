#ifndef BOSCONIAN_LEVELEDITOR_H
#define BOSCONIAN_LEVELEDITOR_H

#include "Game.h"

namespace Game {

    /**
     * The LevelEditor class handles editing and managing levels within the game.
     */
    class LevelEditor {
    private:
        Utils::Config lvl_cfg;

    public:
        /**
         * Constructs a LevelEditor instance with the specified configuration.
         * \param cfg The configuration file for managing levels.
         */
        LevelEditor(std::string cfg = ".\\cfg\\level.ini") : lvl_cfg(cfg) {
            lvl_cfg.add_item("Levels", "levels", Utils::GlobalVars::lvlsInfos);
        }

        /**
         * Saves the edited levels configuration to the configuration file.
         */
        void saveLvls() {
            lvl_cfg.write();
            lvl_cfg.read();
        }

        /**
         * Reads the levels configuration from the configuration file.
         */
        void readLvls() {
            lvl_cfg.read();
        }

        /**
         * Places a base ship at the specified position within the specified level.
         * \param lvl The level number.
         * \param pos The position of the base ship.
         */
        void placeBase(int lvl, Utils::Vector2D pos) {
            for (auto& l : Utils::GlobalVars::lvlsInfos) {
                if (l.lvlNum == lvl) {
                    l.baseShipsPos.push_back(pos);
                    return;
                }
            }
            LOG("Error: Level not found");
        }

        /**
         * Sets the player's spawn position within the specified level.
         * \param lvl The level number.
         * \param pos The player's spawn position.
         */
        void setPlayerSpawnPos(int lvl, Utils::Vector2D pos) {
            for (auto& l : Utils::GlobalVars::lvlsInfos) {
                if (l.lvlNum == lvl) {
                    l.playerPos = pos;
                    return;
                }
            }
            LOG("Error: Level not found");
        }

        /**
         * Undoes the placement of the last base ship within the specified level.
         * \param lvl The level number.
         */
        void undoBase(int lvl) {
            for (auto& l : Utils::GlobalVars::lvlsInfos) {
                if (l.lvlNum == lvl) {
                    l.baseShipsPos.pop_back();
                    return;
                }
            }
            LOG("Error: Level not found");
        }
    };

} // Game

#endif //BOSCONIAN_LEVELEDITOR_H

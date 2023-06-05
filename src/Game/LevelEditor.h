#ifndef BOSCONIAN_LEVELEDITOR_H
#define BOSCONIAN_LEVELEDITOR_H

#include "Game.h"

namespace Game {

    class LevelEditor {
    private:
        Utils::Config lvl_cfg = Utils::Config(".\\cfg\\level.ini");

    public:
        LevelEditor(std::string cfg) {
            //lvl_cfg = Utils::Config(".\\cfg\\level.ini");
        }

        void saveLvls() {
            lvl_cfg.add_item("Level", "baseShipPos", Utils::GlobalVars::lvlsInfos);

            lvl_cfg.write();
            lvl_cfg.read();
        }

        void placeBase(int lvl, Utils::Vector2D pos) {
            for (auto& l : Utils::GlobalVars::lvlsInfos) {
                if (l.lvlNum == lvl) {
                    l.baseShipsPos.push_back(pos);
                    return;
                }
            }
            LOG("Error: Level not found");
        }

        void setPlayerSpawnPos(int lvl, Utils::Vector2D pos) {
            for (auto& l : Utils::GlobalVars::lvlsInfos) {
                if (l.lvlNum == lvl) {
                    l.playerPos = pos;
                    return;
                }
            }
            LOG("Error: Level not found");
        }

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

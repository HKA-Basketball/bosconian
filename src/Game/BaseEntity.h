#ifndef BOSCONIAN_BASEENTITY_H
#define BOSCONIAN_BASEENTITY_H

#include "Entity.h"

namespace Game {

    class BaseEntity {
    private:
        std::vector<Entity*> baseShipEntitys;

    public:
        BaseEntity(Utils::Vector2D pos, float deg, Drawing::Graphics* drawing)
        {
            baseShipEntitys.resize(7);

            std::vector<std::string> baseExpoIMG{"kern", "canon_L", "canon_L_Up", "canon_L_Down", "canon_R", "canon_R_Up", "canon_R_Down"};
            std::vector<std::string> baseIMG{"kern", "canon_L_norm", "canon_L_Up_norm", "canon_L_Down_norm", "canon_R_norm", "canon_R_Up_norm", "canon_R_Down_norm"};
            std::vector<Utils::Vector2D> hitboxSizeList{{32, 32}, {64, 64}, {64, 64}, {64, 64}, {64, 64}, {64, 64}, {64, 64}};
            // From center 0° TODO: 90°
            std::vector<Utils::Vector2D> hitboxPosList{{0, 0}, {0, 0}, {14, -16}, {14, 16}, {0, 0}, {-14, -16}, {-14, 16}};
            std::vector<Utils::Vector2D> posOffsetList{{0, 0}, {-112, 0}, {-62, -80}, {-62, 80}, {112, 0}, {62, -80}, {62, 80}};

            for (int i = 0; i < baseIMG.size(); i++) {
                std::shared_ptr<Drawing::Texture> img = std::make_shared<Drawing::Texture>(drawing, baseIMG[i], deg, true, "spritesheet.png");

                baseShipEntitys[i] = new Entity(pos + posOffsetList[i], deg, img, hitboxPosList[i], hitboxSizeList[i], baseIMG[i].compare("kern") ? 200 : 1500);
                baseShipEntitys[i]->setAngle(deg);
                if (baseIMG[i].compare("kern"))
                    baseShipEntitys[i]->setBehavior(new CanonBehavior(baseExpoIMG[i]));
                else
                    baseShipEntitys[i]->setBehavior(new CoreBehavior());
            }
        }

        ~BaseEntity() {
            // Clean up the entities
            for (Entity *entity: baseShipEntitys) {
                delete entity;
            }
            baseShipEntitys.clear();
        }

        std::vector<Entity*> getEntitys() {
            return baseShipEntitys;
        }

        bool isActive() {
            bool isActive = false;
            for (int i = 1; i < baseShipEntitys.size(); i++) {
                if (baseShipEntitys[i]->isActive() && !baseShipEntitys[i]->isTriggerAnimation()) {
                    isActive = true;
                    break;
                }
            }

            if (!isActive)
                baseShipEntitys[0]->setTriggerAnimation(true);

            return baseShipEntitys[0]->isActive();
        }

        void update(float deltaTime) {
            for (auto& ent : baseShipEntitys) {
                ent->update(deltaTime);
            }
        }

        void draw(float deltaTime) {
            if (baseShipEntitys[0]->isTriggerAnimation() && baseShipEntitys[0]->isActive()) {
                baseShipEntitys[0]->draw(deltaTime);
                return;
            }

            for (auto& ent : baseShipEntitys) {
                ent->draw(deltaTime);
            }
        }
    };

} // Game

#endif //BOSCONIAN_BASEENTITY_H

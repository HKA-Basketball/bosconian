#ifndef BOSCONIAN_BASEENTITY_H
#define BOSCONIAN_BASEENTITY_H

#include "Entity.h"

namespace Game {

    class BaseEntity {
    private:
        std::vector<Entity*> baseShipEntitys;
        bool spy;
        Entity* m_spy = nullptr;

    public:
        BaseEntity(Utils::Vector2D pos, float deg)
        {
            spy = false;
            m_spy = nullptr;
            baseShipEntitys.resize(7);

            std::vector<Utils::Vector2D> hitboxSizeList{{32, 32}, {64, 64}, {64, 64}, {64, 64}, {64, 64}, {64, 64}, {64, 64}};

            std::vector<std::string> baseExpoIMG{"kern", "canon_L", "canon_L_Up", "canon_L_Down", "canon_R", "canon_R_Up", "canon_R_Down"};
            std::vector<std::string> baseIMG{"kern", "canon_L_norm", "canon_L_Up_norm", "canon_L_Down_norm", "canon_R_norm", "canon_R_Up_norm", "canon_R_Down_norm"};
            // 0°
            std::vector<Utils::Vector2D> hitboxPosList{{0, 0}, {0, 0}, {14, -16}, {14, 16}, {0, 0}, {-14, -16}, {-14, 16}};
            std::vector<Utils::Vector2D> posOffsetList{{0, 0}, {-112, 0}, {-62, -80}, {-62, 80}, {112, 0}, {62, -80}, {62, 80}};
            std::vector<float> viewOffset{0.f, 180.f, -90.f, 90.f, 0.f, -90.f, 90.f};

            if (deg > 1.f) {
                baseExpoIMG = {"kern_90", "canon_L_90", "canon_L_Up_90", "canon_L_Down_90", "canon_R_90", "canon_R_Up_90", "canon_R_Down_90"};
                baseIMG = {"kern_90", "canon_L_norm_90", "canon_L_Up_norm_90", "canon_L_Down_norm_90", "canon_R_norm_90", "canon_R_Up_norm_90", "canon_R_Down_norm_90"};
                // 90°
                hitboxPosList = {{0, 0}, {0, 0}, {14, 16}, {-14, 16}, {0, 0}, {14, -16}, {-14, -16}};
                posOffsetList = {{0, 0}, {0, -112}, {80, -62}, {-80, -62}, {0, 112}, {80, 62}, {-80, 62}};
                viewOffset = {0.f, -90.f, 0.f, 180.f, 90.f, 0.f, 180.f};
            }

            for (int i = 0; i < baseIMG.size(); i++) {
                std::shared_ptr<Drawing::Texture> img = std::make_shared<Drawing::Texture>(baseIMG[i], 0.f, true, "spritesheet.png");

                baseShipEntitys[i] = new Entity(pos + posOffsetList[i], 0.f, img, hitboxPosList[i], hitboxSizeList[i], EntityType::Base, (baseIMG[i].find("kern") != std::string::npos) ? 1500 : 200);
                if (baseIMG[i].compare("kern") != std::string::npos) {
                    if (Utils::PlayOptions::maxSpy > 0) {
                        std::shared_ptr<Drawing::Texture> img = std::make_shared<Drawing::Texture>("spy", 0.f, true, "spritesheet.png");
                        m_spy = new Entity((pos + posOffsetList[i]), 0.f, img, EntityType::Moving, 600);
                        m_spy->setBehavior(new SpyBehavior());
                        spy = true;
                        Utils::PlayOptions::maxSpy--;
                    }

                    baseShipEntitys[i]->setBehavior(new CoreBehavior());
                }
                else
                    baseShipEntitys[i]->setBehavior(new CanonBehavior(baseExpoIMG[i], viewOffset[i]));
            }
        }

        ~BaseEntity() {
            if (m_spy) {
                Utils::PlayOptions::maxSpy++;
                delete m_spy;
                m_spy = nullptr;
            }

            // Clean up the entities
            for (Entity *entity: baseShipEntitys) {
                delete entity;
                entity = nullptr;
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
            if (m_spy) {
                if (m_spy->isActive())
                    m_spy->update(deltaTime);
                else {
                    Utils::PlayOptions::maxSpy++;
                    delete m_spy;
                    m_spy = nullptr;
                }
            }

            if (!spy) {
                creatSpy();
            }

            for (auto& ent : baseShipEntitys) {
                ent->update(deltaTime);
            }
        }

        void draw(float deltaTime) {
            if (m_spy && m_spy->isActive())
                m_spy->draw(deltaTime);

            if (baseShipEntitys[0]->isTriggerAnimation() && baseShipEntitys[0]->isActive()) {
                baseShipEntitys[0]->draw(deltaTime);
                return;
            }

            for (auto& ent : baseShipEntitys) {
                ent->draw(deltaTime);
            }
        }

        Entity *getSpy() const {
            return m_spy;
        }
    private:
        void creatSpy() {
            // TODO: Creat Timer
            if (Utils::PlayOptions::maxSpy > 0) {
                std::shared_ptr<Drawing::Texture> img = std::make_shared<Drawing::Texture>("spy", 0.f, true, "spritesheet.png");
                m_spy = new Entity(baseShipEntitys[0]->getOrigin(), 0.f, img, EntityType::Moving, 600);
                m_spy->setBehavior(new SpyBehavior());
                spy = true;
                Utils::PlayOptions::maxSpy--;
            }
        }
    };

} // Game

#endif //BOSCONIAN_BASEENTITY_H

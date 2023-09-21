#ifndef BOSCONIAN_ENTITYVIEW_H
#define BOSCONIAN_ENTITYVIEW_H

#include "EntityModel.h"
#include "../../Sound/SoundManager.h"
#include "../../Physics/Hitbox.h"
#include "../../Drawing/SDL_Rotated_Rect.h"
#include "../../Drawing/Texture.h"
#include "../../../includes.h"

namespace Game {

    class EntityView {
    private:
        std::shared_ptr<Drawing::Texture> obj;
        const EntityModel& m_model;

    public:
        EntityView(std::shared_ptr<Drawing::Texture> img, const EntityModel& model)
            : obj(img)
            , m_model(model)
        {}

        void update() {
            if (!obj)
                return;

            Utils::Vector2D newPosScreen;
            Utils::render::WorldToScreen(m_model.getOrigin(), newPosScreen);
            obj->setPos(newPosScreen - (obj->getSize()*0.5f));
            obj->setAngle(m_model.getAngle());
        }

        void drawEntity() {
            if (!obj)
                return;

            obj->draw();
            drawHitbox();
        }

        void setTexture(std::string name) {
            if (!obj)
                return;

            obj->changeTexture(name, true, "spritesheet.png");
            update();
        }

        void setSize(Utils::Vector2D size) {
            obj->setSize(size);
            update();
        }

    private:
        void drawHitbox() {
            if (!Utils::GlobalVars::debugMode)
                return;

            Utils::Vector2D worldPos = m_model.getHitbox()->getPosition();
            Utils::Vector2D screenPos;
            Utils::render::WorldToScreen(worldPos, screenPos);

            bool isActive = m_model.isActive();
            SDL_Color color{
                    static_cast<Uint8>(isActive ? 0 : 255),
                    static_cast<Uint8>(isActive ? 255 : 0),
                    0,
                    255
            };

            if(!Utils::GlobalVars::collisionMode) {
                auto rect = (SDL_Rect) *m_model.getHitbox();
                rect.x = static_cast<int>(screenPos.x);
                rect.y = static_cast<int>(screenPos.y);

                Drawing::g_drawing->rectangle(color, rect);

            } else {
                auto rotatedRect = (SDL_Rotated_Rect) *m_model.getHitbox();
                rotatedRect.x = static_cast<int>(screenPos.x);
                rotatedRect.y = static_cast<int>(screenPos.y);

                Drawing::g_drawing->rotatedRectangle(color, rotatedRect);
            }
        }
    };
}

#endif //BOSCONIAN_ENTITYVIEW_H

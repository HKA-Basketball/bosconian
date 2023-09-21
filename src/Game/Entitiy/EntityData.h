#ifndef BOSCONIAN_ENTITYSPRITES_H
#define BOSCONIAN_ENTITYSPRITES_H

#include <utility>

#include "../../../includes.h"

namespace Game {


    struct EntityData {
        std::string spriteName;
        int points;
    };

    extern const std::vector<float> entityAngles{0.f, 90.f, 45.f, 135.f, 180.f, -45.f, -90.f, -135.f};

    extern const EntityData playerData{"ship", 0};

    extern const std::vector<EntityData> enemyData = {
            {"E-Type", 70},
            {"I-Type-norm", 50},
            {"P-Type-norm", 60},
    };


    extern const std::vector<EntityData> obstacleData = {
            {"bomb", 20},
            {"astroid-01", 10},
            {"astroid-02", 10},
            {"astroid-03", 10},
    };

    float getRandomAngle() {
        //float ang = ranImg == 4 ? list[rand() % 2] : list[rand() % list.size()];
        int randomIndex = rand() % entityAngles.size();
        return entityAngles[randomIndex];
    }

    float getRandomDirection() {
        return rand() % 2 ? 0.f : 90.f;
    }

    EntityData getRandomEntityData(std::vector<EntityData> entityDatas) {
        int randomIndex = rand() % entityDatas.size();
        return entityDatas[randomIndex];
    }

    Entity* createEntity(const Utils::Vector2D& position, std::vector<EntityData> entityDatas) {
        EntityData entityData = getRandomEntityData(std::move(entityDatas));
        float angle = getRandomAngle();

        std::shared_ptr<Drawing::Texture> img = std::make_shared<Drawing::Texture>(
                entityData.spriteName, angle, true, "spritesheet.png");

        auto* entity = new Entity(position, angle, img, EntityType::NonMoving, entityData.points);
        entity->setBehavior(new NonMovingBehavior());

        return entity;
    }

}

#endif //BOSCONIAN_ENTITYSPRITES_H

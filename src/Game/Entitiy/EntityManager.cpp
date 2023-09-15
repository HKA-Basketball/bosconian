#include "EntityManager.h"

namespace Game {

    void EntityManager::removeEntity(Entity* entity) {
        auto it = std::find(entities.begin(), entities.end(), entity);
        if (it != entities.end()) {
            entities.erase(it);
            delete entity;
        }
    }

    void EntityManager::clearEntities() {
        for (Entity* entity : entities) {
            delete entity;
        }
        entities.clear();
    }

    void EntityManager::update(float deltaTime) {
        std::vector<Entity*> toRemove;

        for (Entity* entity : entities) {
            if (!entity->isActive()) {
                toRemove.push_back(entity);
                continue;
            }
            entity->update(deltaTime);
        }

        for (Entity* entity : toRemove) {
            (entity);
        }
    }

    void EntityManager::render(float deltaTime) {
        for (Entity* entity : entities) {
            entity->draw(deltaTime);
        }
    }

} // Game
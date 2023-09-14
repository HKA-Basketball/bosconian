#include "EntityManager.h"

namespace Game {
    EntityManager::EntityManager() {}

    EntityManager::~EntityManager() {
        clearEntities();
    }

    void EntityManager::addEntity(Entity* entity) {
        entities.push_back(entity);
    }

    void EntityManager::removeEntity(Entity* entity) {
        auto it = std::find(entities.begin(), entities.end(), entity);
        if (it != entities.end()) {
            entities.erase(it);
            delete entity;
            entity = nullptr;
        }
    }

    void EntityManager::clearEntities() {
        for (Entity* entity : entities) {
            delete entity;
        }
        entities.clear();
    }

    void EntityManager::update(float deltaTime) {
        for (Entity* entity : entities) {
            if (!entity->isActive()) {
                removeEntity(entity);
                continue;
            }

            entity->update(deltaTime);
        }
    }

    const std::vector<Entity*> &EntityManager::getEntities() const {
        return entities;
    }

    void EntityManager::render(float deltaTime) {
        for (Entity* entity : entities) {
            entity->draw(deltaTime);
        }
    }

} // Game
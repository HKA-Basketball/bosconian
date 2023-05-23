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
        }
    }

    void EntityManager::clearEntities() {
        for (Entity* entity : entities) {
            delete entity;
        }
        entities.clear();
    }

    void EntityManager::update() {
        for (Entity* entity : entities) {
            entity->update();
        }
    }

    void EntityManager::render() {
        for (Entity* entity : entities) {
            entity->draw();
        }
    }

} // Game
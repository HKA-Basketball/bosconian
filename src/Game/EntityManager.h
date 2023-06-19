#ifndef BOSCONIAN_ENTITYMANAGER_H
#define BOSCONIAN_ENTITYMANAGER_H

#include "../../includes.h"
#include "../Game/Entity.h"

namespace Game {

    class EntityManager {
    private:
        std::vector<Entity*> entities;

    public:
        EntityManager();
        ~EntityManager();

        void addEntity(Entity* entity);
        void removeEntity(Entity* entity);
        void clearEntities();

        void update(float deltaTime);
        void render(float deltaTime);

        const std::vector<Entity *> &getEntities() const;
    };


} // Game

#endif //BOSCONIAN_ENTITYMANAGER_H

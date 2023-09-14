#ifndef BOSCONIAN_ENTITYMANAGER_H
#define BOSCONIAN_ENTITYMANAGER_H

#include "../../../includes.h"
#include "Entity.h"

namespace Game {

    /**
     * The EntityManager class is responsible for managing a collection of entities in the game world.
     */
    class EntityManager {
    private:
        std::vector<Entity*> entities;

    public:
        /**
         * Default constructor for the EntityManager class.
         */
        EntityManager();

        /**
         * Destructor for the EntityManager class.
         * Cleans up memory used by managed entities.
         */
        ~EntityManager();

        /**
         * Add an entity to the list of managed entities.
         * \param entity Pointer to the entity to be added.
         */
        void addEntity(Entity* entity);

        /**
         * Remove an entity from the list of managed entities.
         * \param entity Pointer to the entity to be removed.
         */
        void removeEntity(Entity* entity);

        /**
         * Clear all managed entities from the list.
         */
        void clearEntities();

        /**
         * Update all managed entities based on the elapsed time.
         * \param deltaTime The time elapsed since the last update in seconds.
         */
        void update(float deltaTime);

        /**
         * Render all managed entities with respect to the elapsed time.
         * \param deltaTime The time elapsed since the last render in seconds.
         */
        void render(float deltaTime);

        /**
         * Get a constant reference to the vector of managed entities.
         * \return Constant reference to the vector of managed entities.
         */
        const std::vector<Entity*>& getEntities() const;

    };


} // Game

#endif //BOSCONIAN_ENTITYMANAGER_H

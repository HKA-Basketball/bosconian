#ifndef BOSCONIAN_BASEENTITY_H
#define BOSCONIAN_BASEENTITY_H

#include "Entity.h"
#include "Behaviour/Behaviour.h"
#include "Behaviour/CoreBehaviour.h"
#include "Behaviour/CanonBehaviour.h"
#include "Behaviour/SpyBehaviour.h"
#include "EntityType.h"

namespace Game {

    /**
     * The BaseEntity class represents a collection of entities that function as a single unit.
     */
    class BaseEntity {
    private:
        /** The collection of entities that make up the base ship. */
        std::vector<Entity*> baseEntities;
        /** Flag indicating if a spy entity is present. */
        bool spy;
        /** The spy entity associated with the base ship. */
        Entity* m_spy = nullptr;

    public:
        /**
         * Constructs a BaseEntity instance with the specified position and rotation.
         * \param pos The initial position of the base ship as a Vector2D.
         * \param deg The initial rotation angle of the base ship in degrees.
         */
        BaseEntity(Utils::Vector2D pos, float deg);

        /**
         * Destructor to clean up the BaseEntity instance and its associated entities.
         */
        ~BaseEntity();

        /**
         * Gets the collection of entities within the base ship.
         * \return A vector of Entity pointers representing the entities.
         */
        std::vector<Entity*> getEntities() {
            return baseEntities;
        }

        /**
         * Checks if the base ship is active.
         * \return `true` if the base ship is active, otherwise `false`.
         */
        bool isActive();

        /**
         * Updates the base ship and its entities based on the specified delta time.
         * \param deltaTime The time elapsed since the last update in seconds.
         */
        void update(float deltaTime);

        /**
         * Draws the base ship and its entities based on the specified delta time.
         * \param deltaTime The time elapsed since the last draw in seconds.
         */
        void draw(float deltaTime);

        /**
         * Gets the spy entity associated with the base ship.
         * \return A pointer to the spy entity.
         */
        Entity *getSpy() const {
            return m_spy;
        }

    private:
        /**
         * Creates the spy entity for the base ship.
         */
        void createSpy();
    };

} // Game

#endif //BOSCONIAN_BASEENTITY_H

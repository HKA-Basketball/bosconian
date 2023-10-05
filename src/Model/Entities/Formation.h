#ifndef BOSCONIAN_FORMATION_H
#define BOSCONIAN_FORMATION_H

#include <vector>

#include "Entity.h"
#include "Ship.h"

class Formation {
private:
    Ship* leader;  // The main entity at the center of the formation.
    std::vector<std::pair<Ship*, Vector2D>>* members;  // Other entities and their relative positions to the leader.

public:
    // Constructor, taking a leader entity as a parameter.
    explicit Formation(Ship* leaderEntity) : leader(leaderEntity) {
        members = new std::vector<std::pair<Ship*, Vector2D>>();
    }

    ~Formation() {
        delete leader;

        for (auto& [memberEntity, _] : *members) {
            delete memberEntity;
        }
        members->clear();
        delete members;
    }

    // Add an entity to the formation with a relative position to the leader.
    void addMember(Ship* enemy, const Vector2D& relativePosition) {
        members->emplace_back(enemy, relativePosition);
    }

    // Update the formation:
    // Update the leader and position other entities relative to the leader,
    // considering both position and rotation.
    void update(float deltaTime) {
        leader->update(deltaTime);  // Update the leader.

        // Update members based on the leader's position and rotation.
        for (auto& [memberEntity, relativePos] : *members) {
            memberEntity->update(deltaTime);
            if (leader->isDefeated()) continue;

            Vector2D rotatedPosition = relativePos.rotate(leader->getAngle().toRadians());
            Vector2D newPosition = leader->getPosition() + rotatedPosition;
            memberEntity->setPosition(newPosition);
            memberEntity->setAngle(leader->getAngle());  // Assuming members have the same angle as the leader.
            //memberEntity->update(deltaTime);  // Update each member entity.
        }
    }

    Ship* getLeader() {
        return leader;
    }

    // Getters for the member entities.
    std::vector<std::pair<Ship*, Vector2D>>* getMembers() {
        return members;
    }

    static Formation* createShape(Position* playerPositions) {

        Ship* ship = new Ship({1100, 4000}, 0, playerPositions);
        auto* formation = new Formation(ship);
        ship = new Ship({0, 0}, 0, playerPositions);
        formation->addMember(ship, {75, -75});
        ship = new Ship({0, 0}, 0, playerPositions);
        formation->addMember(ship, {-75, -75});

        return formation;
    }

};

#endif //BOSCONIAN_FORMATION_H

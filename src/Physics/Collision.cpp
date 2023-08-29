#include "Collision.h"

namespace Physics {

    // Helper function to project a polygon onto an axis.
    static void projectPolygon(const Hitbox& hitbox, const Utils::Vector2D& axis, float& min, float& max) {
        Utils::Vector2D screenPosition;
        Utils::render::WorldToScreen(hitbox.getPosition(), screenPosition);

        Utils::Vector2D size = hitbox.getSize()/2;

        float centerProjection = hitbox.getPosition().dot(axis);
        float extentProjection = std::abs(size.x * (axis.dot(Utils::Vector2D(std::cos(hitbox.getAngle()), std::sin(hitbox.getAngle())))) +
                                                  size.y * (axis.dot(Utils::Vector2D(-std::sin(hitbox.getAngle()), std::cos(hitbox.getAngle())))));
        min = centerProjection - extentProjection;
        max = centerProjection + extentProjection;
    }

    // Helper function to check if two intervals overlap.
    bool intervalsOverlap(float minA, float maxA, float minB, float maxB) {
        return (maxA >= minB) && (maxB >= minA);
    }

    bool CollisionManager::checkIntersect(Hitbox hitbox1, Hitbox hitbox2) {

        // aabb collision detection
        if(!Utils::GlobalVars::collisionMode) {
            auto position1 = hitbox1.getPosition();
            auto size1 = hitbox1.getSize();
            auto position2 = hitbox2.getPosition();
            auto size2 = hitbox2.getSize();

            if (position1.x + size1.x < position2.x ||
                position2.x + size2.x < position1.x) {
                return false; // No horizontal overlap
            }

            if (position1.y + size1.y < position2.y ||
                position2.y + size2.y < position1.y) {
                return false; // No vertical overlap
            }

            return true; // Intersection
        }

        // Calculate the unit vectors of hitbox1's local axes.
        float angle1 = hitbox1.getAngle();
        Utils::Vector2D x1(std::cos(angle1), std::sin(angle1));
        Utils::Vector2D y1(-std::sin(angle1), std::cos(angle1));

        // Calculate the unit vectors of hitbox2's local axes.
        float angle2 = hitbox1.getAngle();
        Utils::Vector2D x2(std::cos(angle2), std::sin(angle2));
        Utils::Vector2D y2(-std::sin(angle2), std::cos(angle2));

        // Check for overlap of projections of hitbox1 onto hitbox2's axes.
        for (int i = 0; i < 2; ++i) {
            Utils::Vector2D axis = (i == 0) ? x2 : y2;
            float minA, maxA, minB, maxB;
            projectPolygon(hitbox1, axis, minA, maxA);
            projectPolygon(hitbox2, axis, minB, maxB);
            if (!intervalsOverlap(minA, maxA, minB, maxB)) {
                return false;
            }
        }

        // Check for overlap of projections of hitbox2 onto hitbox1's axes.
        for (int i = 0; i < 2; ++i) {
            Utils::Vector2D axis = (i == 0) ? x1 : y1;
            float minA, maxA, minB, maxB;
            projectPolygon(hitbox1, axis, minA, maxA);
            projectPolygon(hitbox2, axis, minB, maxB);
            if (!intervalsOverlap(minA, maxA, minB, maxB)) {
                return false;
            }
        }

        // The hitboxes are colliding.
        return true;
    }

    bool CollisionManager::entityHit(Game::Projectile *projectile, const Hitbox entityHitbox) {
        if (!projectile->getActive())
            return false;

        if (checkIntersect(projectile->getHitbox(), entityHitbox))
            return true;

        return false;
    }
} // Physics
#include "gtest/gtest.h"
#include "../src/Physics/Hitbox.h"
#include "../src/Physics/HitboxManager.h"

// Hitbox Tests

/**
 * ConstructorTest: Tests if the constructors initialize the Hitbox object with the correct values.
 */
TEST(HitboxTest, ConstructorTest) {
    Vector2D position(0.0f, 0.0f);
    Vector2D size(1.0f, 1.0f);
    float angle = 0.0f;

    Hitbox hitbox(position, size, angle);

    EXPECT_FLOAT_EQ(hitbox.getPosition().x, 0.0f);
    EXPECT_FLOAT_EQ(hitbox.getPosition().y, 0.0f);
    EXPECT_FLOAT_EQ(hitbox.getSize().x, 1.0f);
    EXPECT_FLOAT_EQ(hitbox.getSize().y, 1.0f);
    EXPECT_FLOAT_EQ(hitbox.getAngle().getDegree(), 0.0f);
}

/**
 * ConstructorTest: Tests if the constructors initialize the Hitbox object with the correct values.
 */
TEST(HitboxTest, UpdatePositionTest) {
    Vector2D position(0.0f, 0.0f);
    Vector2D size(1.0f, 1.0f);

    Hitbox hitbox(position, size);
    Vector2D newPosition(1.0f, 1.0f);
    hitbox.updatePosition(newPosition);

    EXPECT_FLOAT_EQ(hitbox.getPosition().x, 1.0f);
    EXPECT_FLOAT_EQ(hitbox.getPosition().y, 1.0f);
    EXPECT_FLOAT_EQ(hitbox.getSize().x, 1.0f);
    EXPECT_FLOAT_EQ(hitbox.getSize().y, 1.0f);
}

/**
 * UpdateSizeTest: Tests if updateSize correctly updates the size of the hitbox.
 */
TEST(HitboxTest, UpdateSizeTest) {
    Vector2D position(0.0f, 0.0f);
    Vector2D size(1.0f, 1.0f);

    Hitbox hitbox(position, size);
    Vector2D newSize(2.0f, 2.0f);
    hitbox.updateSize(newSize);

    EXPECT_FLOAT_EQ(hitbox.getSize().x, 2.0f);
    EXPECT_FLOAT_EQ(hitbox.getSize().y, 2.0f);
}

/**
 * UpdateAngleTest: Tests if updateAngle correctly updates the angle of the hitbox.
 */
TEST(HitboxTest, UpdateAngleTest) {
    Vector2D position(0.0f, 0.0f);
    Vector2D size(1.0f, 1.0f);

    Hitbox hitbox(position, size);
    hitbox.updateAngle(45.0f);

    EXPECT_FLOAT_EQ(hitbox.getAngle().getDegree(), 45.0f);
}

// AABB mode collision tests

/**
 * CheckIntersectAABBTest: check collisions between axis-aligned bounding boxes.
 */
TEST(CollisionManagerTest, CheckIntersectAABBTest) {
    Vector2D position1(0.0f, 0.0f);
    Vector2D size1(1.0f, 1.0f);
    Hitbox hitbox1(position1, size1);

    Vector2D position2(0.5f, 0.5f);
    Vector2D size2(1.0f, 1.0f);
    Hitbox hitbox2(position2, size2);

    EXPECT_TRUE(HitboxManager::areColliding(hitbox1, hitbox2));
}

/**
 * CheckNotIntersectAABBTest: check collisions between axis-aligned bounding boxes.
 */
TEST(CollisionManagerTest, CheckNotIntersectAABBTest) {
    Vector2D position1(0.0f, 0.0f);
    Vector2D size1(1.0f, 1.0f);
    Hitbox hitbox1(position1, size1);

    Vector2D position2(2.0f, 2.0f);
    Vector2D size2(1.0f, 1.0f);
    Hitbox hitbox2(position2, size2);

    EXPECT_FALSE(HitboxManager::areColliding(hitbox1, hitbox2));
}

/**
 * CheckIntersectAABBTest_DifferentSizes: check collisions between axis-aligned bounding boxes with different sizes.
 */
TEST(CollisionManagerTest, CheckIntersectAABBTest_DifferentSizes) {
    Vector2D position1(0.0f, 0.0f);
    Vector2D size1(2.0f, 1.0f); // Changing size
    Hitbox hitbox1(position1, size1);

    Vector2D position2(0.5f, 0.5f);
    Vector2D size2(1.5f, 0.5f); // Changing size
    Hitbox hitbox2(position2, size2);

    EXPECT_TRUE(HitboxManager::areColliding(hitbox1, hitbox2));
}

/**
 * CheckNotIntersectAABBTest_DifferentSizes: check collisions between axis-aligned bounding boxes with different sizes.
 */
TEST(CollisionManagerTest, CheckNotIntersectAABBTest_DifferentSizes) {
    Vector2D position1(0.0f, 0.0f);
    Vector2D size1(2.0f, 1.0f); // Changing size
    Hitbox hitbox1(position1, size1);

    Vector2D position2(3.0f, 3.0f);
    Vector2D size2(1.0f, 0.5f); // Changing size
    Hitbox hitbox2(position2, size2);

    EXPECT_FALSE(HitboxManager::areColliding(hitbox1, hitbox2));
}

// OBB mode collision tests

/**
 * CheckIntersectOBBTest: check collisions between oriented bounding boxes.
 */
TEST(CollisionManagerTest, CheckIntersectOBBTest) {
    Vector2D position1(0.0f, 0.0f);
    Vector2D size1(1.0f, 1.0f);
    Hitbox hitbox1(position1, size1);

    Vector2D position2(0.5f, 0.5f);
    Vector2D size2(1.0f, 1.0f);
    Hitbox hitbox2(position2, size2);

    EXPECT_TRUE(HitboxManager::areColliding(hitbox1, hitbox2));
}

/**
 * CheckNotIntersectOBBTest: check collisions between oriented bounding boxes.
 */
TEST(CollisionManagerTest, CheckNotIntersectOBBTest) {
    Vector2D position1(0.0f, 0.0f);
    Vector2D size1(1.0f, 1.0f);
    Hitbox hitbox1(position1, size1);

    Vector2D position2(2.0f, 2.0f);
    Vector2D size2(1.0f, 1.0f);
    Hitbox hitbox2(position2, size2);

    EXPECT_FALSE(HitboxManager::areColliding(hitbox1, hitbox2));
}

/**
 * CheckIntersectOBBTest_Angle: check collisions between oriented bounding boxes with various angles.
 */
TEST(CollisionManagerTest, CheckIntersectOBBTest_Angle) {
    Vector2D position1(0.0f, 0.0f);
    Vector2D size1(1.0f, 1.0f);
    Hitbox hitbox1(position1, size1, 45.0f); // Adding angle

    Vector2D position2(0.5f, 0.5f);
    Vector2D size2(1.0f, 1.0f);
    Hitbox hitbox2(position2, size2, -30.0f); // Adding angle

    EXPECT_TRUE(HitboxManager::areColliding(hitbox1, hitbox2));
}

/**
 * CheckNotIntersectOBBTest_Angle: check collisions between oriented bounding boxes with various angles.
 */
TEST(CollisionManagerTest, CheckNotIntersectOBBTest_Angle) {
    Vector2D position1(0.0f, 0.0f);
    Vector2D size1(1.0f, 1.0f);
    Hitbox hitbox1(position1, size1, 90.0f); // Adding angle

    Vector2D position2(2.0f, 2.0f);
    Vector2D size2(1.0f, 1.0f);
    Hitbox hitbox2(position2, size2, -45.0f); // Adding angle

    EXPECT_FALSE(HitboxManager::areColliding(hitbox1, hitbox2));
}

/**
 * CheckIntersectOBBTest_EdgeTouch: checks a scenario where two boxes are just barely touching at an edge/corner.
 */
TEST(CollisionManagerTest, CheckIntersectOBBTest_EdgeTouch) {
    Vector2D position1(0.0f, 0.0f);
    Vector2D size1(1.0f, 1.0f);
    Hitbox hitbox1(position1, size1, 45.0f); // Adding angle

    Vector2D position2(0.7f, 0.7f);
    Vector2D size2(1.0f, 1.0f);
    Hitbox hitbox2(position2, size2, 45.0f); // Adding angle

    EXPECT_TRUE(HitboxManager::areColliding(hitbox1, hitbox2));
}

/**
 * CheckIntersectOBBTest_LargeSizes: check the OBB collision system with large bounding boxes.
 */
TEST(CollisionManagerTest, CheckIntersectOBBTest_LargeSizes) {
    Vector2D position1(50.0f, 50.0f);
    Vector2D size1(100.0f, 100.0f); // Large size
    Hitbox hitbox1(position1, size1, 30.0f); // Adding angle

    Vector2D position2(100.0f, 100.0f);
    Vector2D size2(100.0f, 100.0f); // Large size
    Hitbox hitbox2(position2, size2, -30.0f); // Adding angle

    EXPECT_TRUE(HitboxManager::areColliding(hitbox1, hitbox2));
}

/**
 * CheckNotIntersectOBBTest_SmallSizes: check the OBB collision system with small bounding boxes.
 */
TEST(CollisionManagerTest, CheckNotIntersectOBBTest_SmallSizes) {
    Vector2D position1(0.0f, 0.0f);
    Vector2D size1(0.1f, 0.1f); // Small size
    Hitbox hitbox1(position1, size1, 45.0f); // Adding angle

    Vector2D position2(0.11f, 0.11f);
    Vector2D size2(0.1f, 0.1f); // Small size
    Hitbox hitbox2(position2, size2, -45.0f); // Adding angle

    EXPECT_FALSE(HitboxManager::areColliding(hitbox1, hitbox2));
}

/**
 * CheckIntersectOBBTest_ExtremeAngles: checks if the system correctly handles angles
 * beyond the typical range of 0 to 360 degrees.
 */
TEST(CollisionManagerTest, CheckIntersectOBBTest_ExtremeAngles) {
    Vector2D position1(0.0f, 0.0f);
    Vector2D size1(1.0f, 1.0f);
    Hitbox hitbox1(position1, size1, 360.0f); // Extreme angle, effectively 0

    Vector2D position2(0.5f, 0.5f);
    Vector2D size2(1.0f, 1.0f);
    Hitbox hitbox2(position2, size2, -360.0f); // Extreme angle, effectively 0

    EXPECT_TRUE(HitboxManager::areColliding(hitbox1, hitbox2));
}
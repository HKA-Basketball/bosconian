#include "gtest/gtest.h"
#include "../src/Utilities/GlobalVars.h"
#include "../src/Physics/Hitbox.h"
#include "../src/Physics/Collision.h"

// Hitbox Tests

/**
 * ConstructorTest: Tests if the constructors initialize the Hitbox object with the correct values.
 */
TEST(HitboxTest, ConstructorTest) {
    Utils::Vector2D position(0.0f, 0.0f);
    Utils::Vector2D size(1.0f, 1.0f);
    float angle = 0.0f;

    Physics::Hitbox hitbox(position, size, angle);

    EXPECT_FLOAT_EQ(hitbox.getPosition().x, -0.5f);
    EXPECT_FLOAT_EQ(hitbox.getPosition().y, -0.5f);
    EXPECT_FLOAT_EQ(hitbox.getSize().x, 1.0f);
    EXPECT_FLOAT_EQ(hitbox.getSize().y, 1.0f);
    EXPECT_FLOAT_EQ(hitbox.getAngle(), 0.0f);
}

/**
 * ConstructorTest: Tests if the constructors initialize the Hitbox object with the correct values.
 */
TEST(HitboxTest, UpdatePositionTest) {
    Utils::Vector2D position(0.0f, 0.0f);
    Utils::Vector2D size(1.0f, 1.0f);

    Physics::Hitbox hitbox(position, size);
    Utils::Vector2D newPosition(1.0f, 1.0f);
    hitbox.updatePosition(newPosition);

    EXPECT_FLOAT_EQ(hitbox.getPosition().x, 0.5f);
    EXPECT_FLOAT_EQ(hitbox.getPosition().y, 0.5f);
}

/**
 * UpdateSizeTest: Tests if updateSize correctly updates the size of the hitbox.
 */
TEST(HitboxTest, UpdateSizeTest) {
    Utils::Vector2D position(0.0f, 0.0f);
    Utils::Vector2D size(1.0f, 1.0f);

    Physics::Hitbox hitbox(position, size);
    Utils::Vector2D newSize(2.0f, 2.0f);
    hitbox.updateSize(newSize);

    EXPECT_FLOAT_EQ(hitbox.getSize().x, 2.0f);
    EXPECT_FLOAT_EQ(hitbox.getSize().y, 2.0f);
}

/**
 * UpdateAngleTest: Tests if updateAngle correctly updates the angle of the hitbox.
 */
TEST(HitboxTest, UpdateAngleTest) {
    Utils::Vector2D position(0.0f, 0.0f);
    Utils::Vector2D size(1.0f, 1.0f);

    Physics::Hitbox hitbox(position, size);
    hitbox.updateAngle(45.0f);

    EXPECT_FLOAT_EQ(hitbox.getAngle(), 45.0f);
}

/**
 * CastToSDLRectTest: Tests if the Hitbox attributes are correctly transferred to SDL_Rect.
 */
TEST(HitboxTest, CastToSDLRectTest) {
    Utils::Vector2D position(0.0f, 0.0f);
    Utils::Vector2D size(100.0f, 50.0f);

    Physics::Hitbox hitbox(position, size);

    auto rect = static_cast<SDL_Rect>(hitbox);

    EXPECT_EQ(rect.x, -50);
    EXPECT_EQ(rect.y, -25);
    EXPECT_EQ(rect.w, 100);
    EXPECT_EQ(rect.h, 50);
}

/**
 * CastToSDLRotatedRectTest: Tests if the attributes including the angle are correctly transferred to SDL_Rotated_Rect
 */
TEST(HitboxTest, CastToSDLRotatedRectTest) {
    Utils::Vector2D position(0.0f, 0.0f);
    Utils::Vector2D size(100.0f, 50.0f);
    float angle = 45.0f;

    Physics::Hitbox hitbox(position, size, angle);

    auto rotatedRect = static_cast<Drawing::SDL_Rotated_Rect>(hitbox);

    EXPECT_EQ(rotatedRect.x, -50);
    EXPECT_EQ(rotatedRect.y, -25);
    EXPECT_EQ(rotatedRect.w, 100);
    EXPECT_EQ(rotatedRect.h, 50);
    EXPECT_DOUBLE_EQ(rotatedRect.angle, 45.0);
}

/**
 * UpdatePositionAndCastToSDLRotatedRectTest: Tests if the attributes including the angle are correctly transferred to SDL_Rotated_Rect
 */
TEST(HitboxTest, UpdatePositionAndCastToSDLRotatedRectTest) {
    Utils::Vector2D position(0.0f, 0.0f);
    Utils::Vector2D size(100.0f, 50.0f);
    float angle = 45.0f;

    Physics::Hitbox hitbox(position, size, angle);

    Utils::Vector2D newPosition(10.0f, 20.0f);
    hitbox.updatePosition(newPosition);

    auto rotatedRect = static_cast<Drawing::SDL_Rotated_Rect>(hitbox);

    EXPECT_EQ(rotatedRect.x, -40);
    EXPECT_EQ(rotatedRect.y, -5);
    EXPECT_EQ(rotatedRect.w, 100);
    EXPECT_EQ(rotatedRect.h, 50);
    EXPECT_DOUBLE_EQ(rotatedRect.angle, 45.0);
}


// AABB mode collision tests

/**
 * CheckIntersectAABBTest: check collisions between axis-aligned bounding boxes.
 */
TEST(CollisionManagerTest, CheckIntersectAABBTest) {
    Utils::Vector2D position1(0.0f, 0.0f);
    Utils::Vector2D size1(1.0f, 1.0f);
    Physics::Hitbox hitbox1(position1, size1);

    Utils::Vector2D position2(0.5f, 0.5f);
    Utils::Vector2D size2(1.0f, 1.0f);
    Physics::Hitbox hitbox2(position2, size2);

    Utils::GlobalVars::collisionMode = false; // AABB mode
    EXPECT_TRUE(Physics::CollisionManager::checkIntersect(hitbox1, hitbox2));
}

/**
 * CheckNotIntersectAABBTest: check collisions between axis-aligned bounding boxes.
 */
TEST(CollisionManagerTest, CheckNotIntersectAABBTest) {
    Utils::Vector2D position1(0.0f, 0.0f);
    Utils::Vector2D size1(1.0f, 1.0f);
    Physics::Hitbox hitbox1(position1, size1);

    Utils::Vector2D position2(2.0f, 2.0f);
    Utils::Vector2D size2(1.0f, 1.0f);
    Physics::Hitbox hitbox2(position2, size2);

    Utils::GlobalVars::collisionMode = false; // AABB mode
    EXPECT_FALSE(Physics::CollisionManager::checkIntersect(hitbox1, hitbox2));
}

/**
 * CheckIntersectAABBTest_DifferentSizes: check collisions between axis-aligned bounding boxes with different sizes.
 */
TEST(CollisionManagerTest, CheckIntersectAABBTest_DifferentSizes) {
    Utils::Vector2D position1(0.0f, 0.0f);
    Utils::Vector2D size1(2.0f, 1.0f); // Changing size
    Physics::Hitbox hitbox1(position1, size1);

    Utils::Vector2D position2(0.5f, 0.5f);
    Utils::Vector2D size2(1.5f, 0.5f); // Changing size
    Physics::Hitbox hitbox2(position2, size2);

    Utils::GlobalVars::collisionMode = false; // AABB mode
    EXPECT_TRUE(Physics::CollisionManager::checkIntersect(hitbox1, hitbox2));
}

/**
 * CheckNotIntersectAABBTest_DifferentSizes: check collisions between axis-aligned bounding boxes with different sizes.
 */
TEST(CollisionManagerTest, CheckNotIntersectAABBTest_DifferentSizes) {
    Utils::Vector2D position1(0.0f, 0.0f);
    Utils::Vector2D size1(2.0f, 1.0f); // Changing size
    Physics::Hitbox hitbox1(position1, size1);

    Utils::Vector2D position2(3.0f, 3.0f);
    Utils::Vector2D size2(1.0f, 0.5f); // Changing size
    Physics::Hitbox hitbox2(position2, size2);

    Utils::GlobalVars::collisionMode = false; // AABB mode
    EXPECT_FALSE(Physics::CollisionManager::checkIntersect(hitbox1, hitbox2));
}

// OBB mode collision tests

/**
 * CheckIntersectOBBTest: check collisions between oriented bounding boxes.
 */
TEST(CollisionManagerTest, CheckIntersectOBBTest) {
    Utils::Vector2D position1(0.0f, 0.0f);
    Utils::Vector2D size1(1.0f, 1.0f);
    Physics::Hitbox hitbox1(position1, size1);

    Utils::Vector2D position2(0.5f, 0.5f);
    Utils::Vector2D size2(1.0f, 1.0f);
    Physics::Hitbox hitbox2(position2, size2);

    Utils::GlobalVars::collisionMode = true; // OBB mode
    EXPECT_TRUE(Physics::CollisionManager::checkIntersect(hitbox1, hitbox2));
}

/**
 * CheckNotIntersectOBBTest: check collisions between oriented bounding boxes.
 */
TEST(CollisionManagerTest, CheckNotIntersectOBBTest) {
    Utils::Vector2D position1(0.0f, 0.0f);
    Utils::Vector2D size1(1.0f, 1.0f);
    Physics::Hitbox hitbox1(position1, size1);

    Utils::Vector2D position2(2.0f, 2.0f);
    Utils::Vector2D size2(1.0f, 1.0f);
    Physics::Hitbox hitbox2(position2, size2);

    Utils::GlobalVars::collisionMode = true; // OBB mode
    EXPECT_FALSE(Physics::CollisionManager::checkIntersect(hitbox1, hitbox2));
}

/**
 * CheckIntersectOBBTest_Angle: check collisions between oriented bounding boxes with various angles.
 */
TEST(CollisionManagerTest, CheckIntersectOBBTest_Angle) {
    Utils::Vector2D position1(0.0f, 0.0f);
    Utils::Vector2D size1(1.0f, 1.0f);
    Physics::Hitbox hitbox1(position1, size1, 45.0f); // Adding angle

    Utils::Vector2D position2(0.5f, 0.5f);
    Utils::Vector2D size2(1.0f, 1.0f);
    Physics::Hitbox hitbox2(position2, size2, -30.0f); // Adding angle

    Utils::GlobalVars::collisionMode = true; // OBB mode
    EXPECT_TRUE(Physics::CollisionManager::checkIntersect(hitbox1, hitbox2));
}

/**
 * CheckNotIntersectOBBTest_Angle: check collisions between oriented bounding boxes with various angles.
 */
TEST(CollisionManagerTest, CheckNotIntersectOBBTest_Angle) {
    Utils::Vector2D position1(0.0f, 0.0f);
    Utils::Vector2D size1(1.0f, 1.0f);
    Physics::Hitbox hitbox1(position1, size1, 90.0f); // Adding angle

    Utils::Vector2D position2(2.0f, 2.0f);
    Utils::Vector2D size2(1.0f, 1.0f);
    Physics::Hitbox hitbox2(position2, size2, -45.0f); // Adding angle

    Utils::GlobalVars::collisionMode = true; // OBB mode
    EXPECT_FALSE(Physics::CollisionManager::checkIntersect(hitbox1, hitbox2));
}

/**
 * CheckIntersectOBBTest_EdgeTouch: checks a scenario where two boxes are just barely touching at an edge/corner.
 */
TEST(CollisionManagerTest, CheckIntersectOBBTest_EdgeTouch) {
    Utils::Vector2D position1(0.0f, 0.0f);
    Utils::Vector2D size1(1.0f, 1.0f);
    Physics::Hitbox hitbox1(position1, size1, 45.0f); // Adding angle

    Utils::Vector2D position2(0.7f, 0.7f);
    Utils::Vector2D size2(1.0f, 1.0f);
    Physics::Hitbox hitbox2(position2, size2, 45.0f); // Adding angle

    Utils::GlobalVars::collisionMode = true; // OBB mode
    EXPECT_TRUE(Physics::CollisionManager::checkIntersect(hitbox1, hitbox2));
}

/**
 * CheckIntersectOBBTest_LargeSizes: check the OBB collision system with large bounding boxes.
 */
TEST(CollisionManagerTest, CheckIntersectOBBTest_LargeSizes) {
    Utils::Vector2D position1(50.0f, 50.0f);
    Utils::Vector2D size1(100.0f, 100.0f); // Large size
    Physics::Hitbox hitbox1(position1, size1, 30.0f); // Adding angle

    Utils::Vector2D position2(100.0f, 100.0f);
    Utils::Vector2D size2(100.0f, 100.0f); // Large size
    Physics::Hitbox hitbox2(position2, size2, -30.0f); // Adding angle

    Utils::GlobalVars::collisionMode = true; // OBB mode
    EXPECT_TRUE(Physics::CollisionManager::checkIntersect(hitbox1, hitbox2));
}

/**
 * CheckNotIntersectOBBTest_SmallSizes: check the OBB collision system with small bounding boxes.
 */
TEST(CollisionManagerTest, CheckNotIntersectOBBTest_SmallSizes) {
    Utils::Vector2D position1(0.0f, 0.0f);
    Utils::Vector2D size1(0.1f, 0.1f); // Small size
    Physics::Hitbox hitbox1(position1, size1, 45.0f); // Adding angle

    Utils::Vector2D position2(1.0f, 1.0f);
    Utils::Vector2D size2(0.1f, 0.1f); // Small size
    Physics::Hitbox hitbox2(position2, size2, -45.0f); // Adding angle

    Utils::GlobalVars::collisionMode = true; // OBB mode
    EXPECT_FALSE(Physics::CollisionManager::checkIntersect(hitbox1, hitbox2));
}

/**
 * CheckIntersectOBBTest_ExtremeAngles: checks if the system correctly handles angles
 * beyond the typical range of 0 to 360 degrees.
 */
TEST(CollisionManagerTest, CheckIntersectOBBTest_ExtremeAngles) {
    Utils::Vector2D position1(0.0f, 0.0f);
    Utils::Vector2D size1(1.0f, 1.0f);
    Physics::Hitbox hitbox1(position1, size1, 360.0f); // Extreme angle, effectively 0

    Utils::Vector2D position2(0.5f, 0.5f);
    Utils::Vector2D size2(1.0f, 1.0f);
    Physics::Hitbox hitbox2(position2, size2, -360.0f); // Extreme angle, effectively 0

    Utils::GlobalVars::collisionMode = true; // OBB mode
    EXPECT_TRUE(Physics::CollisionManager::checkIntersect(hitbox1, hitbox2));
}


int main(int argc, char **argv) {
    // make sure that collision mode is on default
    Utils::GlobalVars::collisionMode = false;

    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
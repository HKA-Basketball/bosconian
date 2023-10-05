#include "gtest/gtest.h"
#include "../src/Utilities/Math.h"
#include "../src/Utilities/Random.h"
#include "../src/Model/World.h"

#define PRINTTEST(num, text) printf("Test-%d: %s\n", num, text);

// Tests for normalizeAngle180
TEST(UtilsTests, NormalizeAngle180) {
    PRINTTEST(1, "NormalizeAngle180");
    EXPECT_FLOAT_EQ(Math::normalizeAngle180(270.0), -90.0);
    EXPECT_FLOAT_EQ(Math::normalizeAngle180(-450.0), -90.0);
    EXPECT_FLOAT_EQ(Math::normalizeAngle180(90.0), 90.0);
}

// Tests for normalizeAngle360
TEST(UtilsTests, NormalizeAngle360) {
    PRINTTEST(1, "NormalizeAngle360");
    EXPECT_FLOAT_EQ(Math::normalizeAngle360(450.0), 90.0);
    EXPECT_FLOAT_EQ(Math::normalizeAngle360(-90.0), 270.0);
    EXPECT_FLOAT_EQ(Math::normalizeAngle360(-720.0), 0.0);
}

// Test for RandomInt (this is a probabilistic test)
TEST(UtilsTests, RandomInt) {
    PRINTTEST(1, "RandomFloat");
    int min = 0;
    int max = 10;
    for (int i = 0; i < 1000; ++i) {
        int random = Random::randomInt(min, max);
        EXPECT_GE(random, min);
        EXPECT_LE(random, max);
    }
}

// Test for RandomFloat (this is a probabilistic test)
TEST(UtilsTests, RandomFloat) {
    PRINTTEST(1, "RandomFloat");
    float min = 0.0;
    float max = 10.0;
    for (int i = 0; i < 1000; ++i) {
        float random = Random::randomFloat(min, max);
        EXPECT_GE(random, min);
        EXPECT_LE(random, max);
    }
}

// Tests for wrapPos
TEST(UtilsTests, WrapPos) {
    PRINTTEST(1, "WrapPos");
    Vector2D newPosition1 = {3100, 4200};
    Vector2D newPosition2 = {364, 301};
    Vector2D newPosition3 = {-1500, -8150};

    newPosition1 = World::wrapPosition(newPosition1);
    newPosition2 = World::wrapPosition(newPosition2);
    newPosition3 = World::wrapPosition(newPosition3);

    EXPECT_EQ(newPosition1.x, 100);
    EXPECT_EQ(newPosition1.y, 200);
    EXPECT_EQ(newPosition2.x, 364);
    EXPECT_EQ(newPosition2.y, 301);
    EXPECT_EQ(newPosition3.x, 1500);
    EXPECT_EQ(newPosition3.y, 3850);
}
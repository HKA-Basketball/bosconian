#include "gtest/gtest.h"
#include "../src/Utilities/GlobalVars.h"

#define PRINTTEST(num, text) printf("Test-%d: %s\n", num, text);

// Tests for normalizeAngle180
TEST(UtilsTests, NormalizeAngle180) {
    PRINTTEST(1, "NormalizeAngle180");
    EXPECT_FLOAT_EQ(Utils::Math::normalizeAngle180(270.0), -90.0);
    EXPECT_FLOAT_EQ(Utils::Math::normalizeAngle180(-450.0), -90.0);
    EXPECT_FLOAT_EQ(Utils::Math::normalizeAngle180(90.0), 90.0);
}

// Tests for normalizeAngle360
TEST(UtilsTests, NormalizeAngle360) {
    PRINTTEST(1, "NormalizeAngle360");
    EXPECT_FLOAT_EQ(Utils::Math::normalizeAngle360(450.0), 90.0);
    EXPECT_FLOAT_EQ(Utils::Math::normalizeAngle360(-90.0), 270.0);
    EXPECT_FLOAT_EQ(Utils::Math::normalizeAngle360(-720.0), 0.0);
}

// Test for RandomFloat (this is a probabilistic test)
TEST(UtilsTests, RandomFloat) {
    PRINTTEST(1, "RandomFloat");
    float min = 0.0;
    float max = 10.0;
    for (int i = 0; i < 1000; ++i) {
        float random = Utils::Math::RandomFloat(min, max);
        EXPECT_GE(random, min);
        EXPECT_LE(random, max);
    }
}

// Tests for rectIntersect
TEST(UtilsTests, RectIntersect) {
    PRINTTEST(1, "RectIntersect");
    SDL_Rect rect1 = {0, 0, 10, 10};
    SDL_Rect rect2 = {5, 5, 10, 10};
    SDL_Rect rect3 = {20, 20, 10, 10};

    EXPECT_TRUE(Utils::Math::rectIntersect(rect1, rect2));
    EXPECT_FALSE(Utils::Math::rectIntersect(rect1, rect3));
}

// Tests for wrapPos
TEST(UtilsTests, WrapPos) {
    PRINTTEST(1, "WrapPos");
    Utils::Vector2D newPosition1 = {100, 100};
    Utils::Vector2D newPosition2 = {300, 300};

    Utils::GlobalVars::cameraPos = {0, 0};
    Utils::GlobalVars::lvlWidth = 200;
    Utils::GlobalVars::lvlHeight = 200;

    Utils::Math::wrapPos(&newPosition1);
    Utils::Math::wrapPos(&newPosition2);

    EXPECT_EQ(newPosition1.x, 100);
    EXPECT_EQ(newPosition1.y, 100);
    EXPECT_EQ(newPosition2.x, 100);
    EXPECT_EQ(newPosition2.y, 100);
}
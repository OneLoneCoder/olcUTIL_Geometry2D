#include <gtest/gtest.h>
#include "../olcUTIL_Geometry2D.h"

using namespace olc::utils::geom2d;

class CircleTest : public ::testing::Test
{
protected:
    void SetUp() override
    {
        // Initialize the circle
        c = circle<float>({{0.0f, 0.0f}, 10.0f});
    }

    circle<float> c;
};

// The test name consists of the module that is tested, the scenario under which it is tested and the expected behavior

TEST_F(CircleTest, circle_contains_PointOnCircleBoundary_True)
{
    // Create a point on the circle boundary
    olc::v_2d<float> p(0.0f, 10.0f);

    // Check if the circle contains the point
    bool result = contains(c, p);

    // Assert that the result is true
    ASSERT_TRUE(result);
}

TEST_F(CircleTest, circleContains_PointIsInside_True)
{
    // Create a point inside the circle
    olc::v_2d<float> p(1.0f, 1.0f);

    // Check if the circle contains the point
    bool result = contains(c, p);

    // Assert that the result is true
    ASSERT_TRUE(result);
}

TEST_F(CircleTest, circleContains_PointIsOutside_False)
{
    // Create a point outside the circle
    olc::v_2d<float> p(12.0f, 12.0f);

    // Check if the circle contains the point
    bool result = contains(c, p);

    // Assert that the result is false
    ASSERT_FALSE(result);
}

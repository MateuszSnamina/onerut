#include <gtest/gtest.h>

TEST(test_suite, test0) {
    ASSERT_TRUE(true);
    ASSERT_FALSE(false);
    EXPECT_TRUE(true);
    EXPECT_FALSE(false);
    EXPECT_EQ(7,7);
}

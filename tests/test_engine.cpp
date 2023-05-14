#include <gtest/gtest.h>

#include <autograd/autograd.hpp>
#include <iostream>

int main(int argc, char** argv)
{
  testing::InitGoogleTest(&argc, argv);

  return RUN_ALL_TESTS();
}

TEST(sample_test_case, sample_test) { EXPECT_EQ(1, 1); }
#include <gtest/gtest.h>

#include <autograd/autograd.hpp>
#include <iostream>

using namespace autograd;

TEST(sample_test_case, sample_test)
{
  auto a = Variable<int>(1);
  auto b = Variable<int>(Variable<int>(2));
  auto c = Variable(a);

  EXPECT_EQ(a, c);
  EXPECT_TRUE(a == c);
  EXPECT_FALSE(a == b);
}

TEST(arithmetic_operations, addition_assignment)
{
  // integers
  auto a = Variable<int>(1);
  auto b = Variable<int>(2);

  a += b;
  EXPECT_EQ(a, 3);

  b += 3;
  EXPECT_EQ(b, 5);
}

TEST(arithmetic_operations, addition)
{
  // integers
  auto a = Variable<int>(1);
  auto b = Variable<int>(2);
  auto c = Variable<int>(3);

  // variable <= variable + number
  a = a + 4;
  EXPECT_EQ(a, 5);

  // variable <= number + variable
  b = 3 + b;
  EXPECT_EQ(b, 5);

  // variable <= variable + variable
  EXPECT_EQ(c, 3);
  c = a + b;
  EXPECT_EQ(c, 10);
}

int main(int argc, char** argv)
{
  testing::InitGoogleTest(&argc, argv);

  return RUN_ALL_TESTS();
}
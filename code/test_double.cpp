#include <iostream>
#include "gtest/gtest.h"

double calculate_norm(int array[])
{
  // Some complex calculation and finally return the norm (a dummy value here)
  return 1.0;
}

double norm_stub(int array[])
{
  return 10.0;
}

void normalize_v1(int array[], int length)
{
  double norm{calculate_norm(array)};

  for (int i{0}; i < length; ++i)
  {
    array[i] /= norm;
  }
}

void normalize_v2(
    int array[],
    int length,
    std::function<double(int[])> func = calculate_norm)
{
  double norm{func(array)};

  for (int i{0}; i < length; ++i)
  {
    array[i] /= norm;
  }
}

TEST(NormalizeTest, ResultCorrect)
{

  double factor{norm_stub({})};
  int length{3};
  int input[]{1, 2, 3};
  int copy[]{1, 2, 3};

  normalize_v2(input, length, norm_stub);

  for (int i{0}; i < length; ++i)
  {
    EXPECT_EQ(input[i] / factor, copy[i]);
  }
}

int main(int argc, char **argv)
{
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}

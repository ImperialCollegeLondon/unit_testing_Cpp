#include <iostream>
#include <cmath>
#include "gtest/gtest.h"

/// @brief A "complex" calculation of the norm.
/// @param array The vector to calculate the norm for.
/// @return The actual norm of the vector.
double calculate_norm(std::vector<double> array)
{
  double output{0};
  for (int i{0}; i < array.size(); ++i)
  {
    output += array[i] * array[i];
  }
  return std::sqrt(output);
}

/// @brief Just a stub, so we can get a simple value to test things with.
/// @param array The vector to calculate the norm for.
/// @return The norm, a dummy value in this case.
double norm_stub(std::vector<double> array)
{
  return 10.0;
}

/// @brief We cannot do dependency injection, so the result depends on what calculate_norm is doing
/// @param array The vector to normalize.
void normalize_v1(std::vector<double> array)
{
  double norm{calculate_norm(array)};

  for (int i{0}; i < array.size(); ++i)
  {
    array[i] /= norm;
  }
}

/// @brief The norm calculation is injected, so we control that value.
/// @param array The vector to normalize.
/// @param func The function used to calculate the norm.
void normalize_v2(
    std::vector<double> array,
    std::function<double(std::vector<double>)> func = calculate_norm)
{
  double norm{func(array)};

  for (int i{0}; i < array.size(); ++i)
  {
    array[i] /= norm;
  }
}

TEST(NormalizeTest, WithoutDependencyInjection)
{
  std::vector<double> input{1, 2, 3};

  // We need the exact value of the norm in order to check that
  // the calculation is correct.
  double factor{calculate_norm(input)};
  std::vector<double> copy{1, 2, 3};

  normalize_v2(input);

  for (int i{0}; i < input.size(); ++i)
  {
    EXPECT_EQ(input[i] / factor, copy[i] / factor);
  }
}

TEST(NormalizeTest, WithDependencyInjection)
{
  std::vector<double> input{1, 2, 3};

  // Here the exact value of the norm is meaningless as we control it.
  double factor{norm_stub({})};
  std::vector<double> copy{1, 2, 3};

  normalize_v2(input, norm_stub);

  for (int i{0}; i < input.size(); ++i)
  {
    EXPECT_EQ(input[i] / factor, copy[i] / factor);
  }
}

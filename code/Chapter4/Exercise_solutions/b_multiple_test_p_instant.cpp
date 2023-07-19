#include <gtest/gtest.h>

// Define your function to be tested here.
int Sum(int a, int b) {
    return a + b;
}

// function to multiply two numbers
double Multiply(double a, double b) {
    return a * b;
}

// Function to calculate a raised to the power of b (integer) without using pow function
double Power(double a, int b) {
    double result = 1;
    for(int i = 0; i < b; i++) {
        result *= a;
    }
    return result;
}

// Define a test fixture class
class ParameterizedTest : public testing::TestWithParam<std::pair<int, int>> {
};

// Define the test case with the parameterized test
TEST_P(ParameterizedTest, TestSum) {
    // Get the parameter values
    int a = GetParam().first;
    int b = GetParam().second;

    // Call your normal function
    int result = Sum(a, b);

    // Perform assertion
    ASSERT_EQ(a + b, result);
}

// Define the test data
INSTANTIATE_TEST_SUITE_P(Default, ParameterizedTest, testing::Values(
    std::make_pair(1, 1),
    std::make_pair(2, 3),
    std::make_pair(-5, 10)
));

// Define the test case with the parameterized test for multiply function.
TEST_P(ParameterizedTest, TestMultiply) {
    // Get the parameter values
    int a = GetParam().first;
    int b = GetParam().second;

    // Call your normal function
    int result = Multiply(a, b);

    // Perform assertion
    ASSERT_EQ(a * b, result);
}


// Define a test fixture class
class ParameterizedTest_Power : public testing::TestWithParam<std::tuple<double, int, double>> {
};


//Check if the power function works fine for different values of a and b
TEST_P(ParameterizedTest_Power, TestPowerFun)
{
    // Get the parameter values
    double a, answer;
    int b;
    std::tie(a, b, answer) = GetParam();

    // For C++ 17, you can comment the above 3 lines and uncomment the below one.
    //auto [a, b, answer] = GetParam();

    // Call your normal function
    double result = Power(a, b);

    // Perform assertion (Since floating point values are being compared, use `ASSERT_DOUBLE_EQ`).
    // For more details, please see:- https://google.github.io/googletest/reference/assertions.html#floating-point
    ASSERT_DOUBLE_EQ(answer, result);
}

// Define the test data
INSTANTIATE_TEST_SUITE_P(PowTest, ParameterizedTest_Power, testing::Values(
    std::make_tuple(1, 1, 1),
    std::make_tuple(2, 3, 8),
    std::make_tuple(2.5, 2, 6.25)
));

int main(int argc, char** argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}


//Compilation command:
// g++ b_multiple_test_p_instant.cpp -lgtest -lpthread
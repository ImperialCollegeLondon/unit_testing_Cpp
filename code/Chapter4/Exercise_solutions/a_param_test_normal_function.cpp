#include <gtest/gtest.h>

// Define your function to be tested here.
int Sum(int a, int b) {
    return a + b;
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

int main(int argc, char** argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

// Compilation command:
// g++ a_param_test_normal_function.cpp -lgtest -lgtest_main -lpthread -o param_test_normal_function
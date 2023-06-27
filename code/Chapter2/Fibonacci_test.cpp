#include <iostream>
#include "gtest/gtest.h"

// Returns the n-th term of the Fibonacci sequence.
int recursive_fibonacci(int n)
{
    if (n <= 1) {
        return n;
    } else {
        return recursive_fibonacci(n - 1) + recursive_fibonacci(n - 2);
    }
}

TEST(FibonacciTest, HandlesZeroInput) {
    EXPECT_EQ(recursive_fibonacci(0), 0);
}

TEST(FibonacciTest, HandlesValueOneAsInput) {
    EXPECT_EQ(recursive_fibonacci(1), 1);
}

TEST(FibonacciTest, HandlesPositiveInput) {
    EXPECT_EQ(recursive_fibonacci(5), 5);
}

TEST(FibonacciTest, HandlesNegativeInput) {
    EXPECT_EQ(recursive_fibonacci(-3), -3);
}


int main(int argc, char **argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
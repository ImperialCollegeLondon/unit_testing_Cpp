---
title: "Introduction to Unit Testing using Google Test"
teaching: TBC
exercises: TBC
questions:
- "What framework/libraries can be used for unit testing in C++?"
- "What is GoogleTest?"
- "How to write unit tests with GoogleTest?"
objectives:
- "Understand the basic components of a unit test"
- "Understand how to write a unit test using google test library?"
- "Understand how to compile and run the test?"
- "Understand some of the macros available in google test"
keypoints:
- "We learnt about some of the popular testing frameworks for C++."
- "We learnt about Googletest and how to use it to write our tests."
- "We learnt about anatomy of a unit test and how to write effective unit tests."
- "Finally, we saw an example to demonstrate the above concepts."
---

## 1. Popular frameworks for testing in C++

There are a number of popular frameworks that can be used for testing in C++. A few of them are mentioned below:-

- [GoogleTest](https://google.github.io/googletest/)
- [Boost.Test](https://www.boost.org/doc/libs/1_82_0/libs/test/doc/html/index.html)
- [CppUtest](http://cpputest.github.io/)
- [Catch2](https://github.com/catchorg/Catch2)
- [UT++](https://boost-ext.github.io/ut/)
- [doctest](https://github.com/doctest/doctest)

In this course, we will focus mainly on GoogleTest.

## 2. A brief about GoogleTest

Simply defining, GoogleTest is a testing framework developed by Google's testing technology team to develop and write C++ tests.  GoogleTest offers multiple advantages over other frameworks:-

1. **Comprehensive Features**: Google Test provides a rich set of features, including a wide range of assertion macros, test fixtures, parameterized tests, test discovery, test filtering, and powerful mocking capabilities. It offers a complete testing framework that can handle various testing scenarios.
2. **Integration with Google Test ecosystem**: Google Test integrates well with other tools and libraries in the Google Test ecosystem. For example, it can be seamlessly used with Google Mock for creating mock objects and behaviours. This integration enhances the testing capabilities and flexibility.
3. **Large and Active Community**: Google Test has a large and active community of developers. This means that there is ample support available in terms of documentation, tutorials, forums, and online resources. 
4. **Mature and Stable**: It is a mature and stable framework that has been used extensively in industry projects and open-source software. 
5. **Wide Platform Support**: Google Test supports multiple platforms, including Windows, Linux, macOS, and various compilers. It is compatible with popular development environments and build systems, making it suitable for a wide range of C++ projects.
6. **Flexible and Extensible**: Google Test provides flexibility in test organization and customization. It allows you to structure your tests using test cases and test suites. You can also define custom test fixtures and customise test execution and reporting. Additionally, Google Test can be extended with custom assertion macros and utilities to suit your specific testing needs.

## 3. Writing Unit test using GoogleTest

For this episode, we will consider the same example `fibonacci.cpp` that we used previously. There we identified 3 possible cases when using the `recursive_fibonacci` function for which we wrote some manual tests:

- `n` equal to 0 or 1
- `n` a negative number
- `n` a positive number greater than 1

To demonstrate how to use GoogleTest, we will simply be converting these tests that we wrote manually in the same file using GoogleTest framework. Section 5 below will describe the anatomy of a test, but first lets see how they look like in the practical case.
For using GoogleTest in your code, you need to follow the following steps in general.



### 3.1. Adding the required header files

The first step would be to add the required header files in your program. For Googletest, you would need to add the following line in your code.

```cpp
#include "gtest/gtest.h"
```

### 3.2. Create your tests

The next step would be to to define your test. Googletest uses the following convention in naming various tests.

```cpp
TEST(TestSuiteName, TestName)
{
    // Test logic and assertions
}
```

The different parts in the above cell have the following meaning

- `TEST`: This is the macro provided by the Google Test framework to define a test case.
- `TestSuiteName`: It is the name of the test suite or test fixture. It groups related tests together. It should be a valid C++ identifier.
- `TestName`: It is the name of the individual test case within the test suite. It should also be a valid C++ identifier.
- `Test logic and assertions`: This is the body of the test case where you write the actual test code, including any necessary assertions to verify the expected behaviour. The section `Test Assertions` describes more about various assertions available in GoogleTest.

### 3.3. Initialise GoogleTest framework in your main

For this sub-section, we are assuming that you are writing your own main function (GoogleTest also allows you to run your code without your own main function by linking to a main function provided in `lgest_main`. Please see the next section for more details). You would need to include the following lines in your main function as shown below.

```cpp
int main(int argc, char **argv)
{
    // Initialise GoogleTest Framework
    testing::InitGoogleTest(&argc, argv);
    
    // Instruction to Run the test cases.
    return RUN_ALL_TESTS();
}
```

The `RUN_ALL_TESTS()` is typically called from `main` and when it is invoked, it scans the program for all the test cases and  test methods defined using the `test` macro. It then executes each test case and captures the results of each individual test method within the test case. After running all the tests, it provides a summary of the test results, including the number of tests run, passed, and failed.

### 3.4. Compile and run your program

In order to compile your program and link with the required libraries, you can use the following instruction as a template. Please remember to modify the paths according to your system and location of the files.

```bash
# For compiling and linking, please use the instruction below
$ g++ your_code.cpp -I path_to_your_gtest.h -L path_to_your_lgtest.a -lgtest -lpthread -o your_executable_name
 
# Run your code  
$ ./your_executable_name
```

If you do not want to write your main function, you can link against the one provided in the `libgtest_main.a` library by using the following instruction.

```bash
$ g++ your_code.cpp -I path_to_your_gtest.h -L path_to_your_lgtest.a -lgtest_main -lgtest -lpthread -o your_executable_name
```
## 4. Test Assertions in GoogleTest

Googletest offers many types of assertions as described in [GoogleTest Assertions](http://google.github.io/googletest/reference/assertions.html). A few of them are described below as they will be used in our upcoming sections/chapters.

<br> </br>
**1. Equality Assertions**: Equality assertions are used to compare values for equality. The most commonly used assertion is `ASSERT_EQ(expected, actual)`, which verifies that the `expected` and `actual` values are equal. For example:

```cpp
ASSERT_EQ(expected_value, your_function(function_arguments));  
// Verify that the expexted value is equal to the value returned by your function.

// You can alo change the order if you prefer.
ASSERT_EQ(your_function(function_arguments), expected_value);
```

Other useful equality assertions include `ASSERT_NE`, `ASSERT_LT`, `ASSERT_LE`, `ASSERT_GT`, and `ASSERT_GE` for performing inequality comparisons.

<br> </br>
**2. Boolean Assertions**: Boolean assertions are used to verify boolean conditions. For example, `ASSERT_TRUE(condition)` checks that the `condition` is `true`, while `ASSERT_FALSE(condition)` ensures that the `condition` is `false`.

```cpp
ASSERT_TRUE(isValid);  // Verify that the isValid flag is true
ASSERT_FALSE(hasError);  // Verify that the hasError flag is false
```


<br> </br>
**3. Exception Assertions**: Exception assertions are used to validate that specific exceptions are thrown during the execution of code. In Google Test, you can use the `ASSERT_THROW(statement, exceptionType)` assertion. For example:

```cpp
ASSERT_THROW(throwException(), std::runtime_error);  // Verify that throwException() throws a std::runtime_error
```


<br> </br>
**4. String Assertions**: String assertions are used to compare string values. Google Test provides various string assertions, such as `ASSERT_STREQ`, `ASSERT_STRNE`, `ASSERT_STRCASEEQ`, and `ASSERT_STRCASENE`. These assertions allow you to compare strings for equality, inequality, or case-insensitive equality.

```
ASSERT_STREQ("Hello", getString());  // Verify that getString() returns the exact string "Hello"
ASSERT_STRCASEEQ("hello", getLowerCaseString());  // Verify that getLowerCaseString() returns "hello" in a case-insensitive manner
```

The majority of the macros listed above come as a pair with an `EXPECT_` variant and an `ASSERT_` variant. Upon failure, `EXPECT_` macros generate nonfatal failures and allow the current function to continue running, while `ASSERT_` macros generate fatal failures and abort the current function.

All assertion macros support streaming a custom failure message into them with the `<<` operator, for example:

```cpp
EXPECT_TRUE(my_condition) << "My condition is not true";
```


<br> </br>
## 5. Anatomy of a Unit Test

A Unit test in general follows a three step structure as mentioned below:-

1. **Setup**: In the setup phase, we prepare the necessary preconditions for the unit test. This involves creating any required objects, initialising variables, and setting up the environment to mimic the desired test scenario. The setup step ensures that the unit being tested has the necessary dependencies and context to execute successfully.
2. **Execution**: The execution step involves invoking the unit under test with the specified inputs or parameters. This is the actual execution of the code being tested. The unit is executed with the predetermined inputs, and its output or behavior is observed.
3. **Verification**: In the verification step, we check whether the actual output or behaviour matches the expected result. This typically involves making assertions or comparisons between the observed output and the expected output. If the assertions pass, the test is considered successful. Otherwise, if any assertion fails, it indicates a discrepancy between the expected and actual outcomes, highlighting a potential issue in the unit being tested.

This 3 step structure if often referred as `Arrange-Act-Assert (AAA)` in some textbooks and online resources. 


<br> </br>
## 6. Writing Effective Unit Tests

For writing your Unit Tests, it is advisable to follow the guidelines given below.

1. **Clear and Descriptive Names**: Choose meaningful names for your test methods that accurately describe the scenario being tested. A good test method name should clearly convey the input, expected behavior, or outcome being verified. Avoid vague or generic names that don't provide sufficient information about the purpose of the test.

   a. `calculateTotal_WithValidInputs_ShouldReturnCorrectSum`

   b. `validateEmail_WithInvalidFormat_ShouldReturnFalse`

   

2. **Consistent Formatting**: Consistency in naming conventions helps maintain a uniform and predictable test suite. Choose a naming style and stick to it throughout your test methods. Some common conventions include using **CamelCase** or **underscore-separated** words. Additionally, consider using a prefix like `test_` or a suffix like `should` to distinguish test methods from regular code.
3. **Single Responsibility**: Each test method should focus on testing a single aspect or behaviour of the unit under test. Avoid testing multiple scenarios within a single test method, as it can make the test less readable and harder to diagnose when failures occur. Instead, break down complex scenarios into multiple smaller tests, each targeting a specific case or condition.
4. **Test Data Organization**: Separate the test data from the test methods. Consider using dedicated variables or data structures to store test data. This allows for better readability and maintainability, as changes to the test data can be easily managed without modifying the test methods themselves.

## 7. Unit Test for the Fibonacci Sequence

With the above guidelines in mind, we can write some of the unit tests for our `Fibonacci.cpp` that we learnt in Chapter 1. The complete code is given below and can be found in [Chapter2](../code/Chapter2/Fibonacci_test.cpp).

```cpp
#include <iostream>
#include "gtest/gtest.h"

/*Returns the n'th term of the Fibonacci sequence.*/
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

int main(int argc, char **argv)
{
testing::InitGoogleTest(&argc, argv);
return RUN_ALL_TESTS();
}
```

On compiling and running above program, we get the following output.

```bash
[==========] Running 3 tests from 1 test suite.
[----------] Global test environment set-up.
[----------] 3 tests from FibonacciTest
[ RUN      ] FibonacciTest.HandlesZeroInput
[       OK ] FibonacciTest.HandlesZeroInput (0 ms)
[ RUN      ] FibonacciTest.HandlesValueOneAsInput
[       OK ] FibonacciTest.HandlesValueOneAsInput (0 ms)
[ RUN      ] FibonacciTest.HandlesPositiveInput
[       OK ] FibonacciTest.HandlesPositiveInput (0 ms)
[----------] 3 tests from FibonacciTest (0 ms total)

[----------] Global test environment tear-down
[==========] 3 tests from 1 test suite ran. (0 ms total)
[  PASSED  ] 3 tests.
```
### 7.1 Exercise

Modify the above program to test for the negative values.

**Solution**

Add the following lines in your code.

```cpp
TEST(FibonacciTest, HandlesNegativeInput) {
    EXPECT_EQ(recursive_fibonacci(-3), -3);
}

```

### Summary
In this chapter, we learnt about the basics of GoogleTest and how to use it to write tests in C++.

{% include links.md %}
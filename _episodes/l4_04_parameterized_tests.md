---
title: "Parameterised Tests using GoogleTest"
teaching: TBC
exercises: TBC
questions:
- "What is a parameterised test?"
- "How to write your own parameterised tests using GoogleTest?"
objectives:
- "Understand why do we need a parameterised test."
- "Understand how to create a parameterised test using GoogleTest."
- "Understand the advantages of parameterised tests."
- "Understand how to combine a test fixtures with parameterised test."
keypoints:
- "We learnt about parameterised tests in GoogleTest."
- "We learnt how to create our own parameterised tests."
- "We learnt how to combine test fixture with parameterised test."
---

## 1. Introduction to Parameterised Tests
**Parameterized tests**, also known as **data-driven tests**, are a feature provided by testing frameworks like Google Test that allows us to write a single test case that can be executed with different sets of test data or inputs. Instead of duplicating similar test cases with slight variations, parameterized tests enable us to define a test once and run it with multiple inputs or test data.

In order to understand the importance of parameterised tests and why do we need them, let us consider a very small example. For this chapter, we will be using our `Employee` class that we created in last chapter.

Let us suppose that we want to test that net bonus calculation works fine for different number of years of expereince. Remember that our `Employee` class adds an additional bonus of $1000£$ when an employee has worked for more than 10 years. As a first approach, we might be tempted to write multiple tests for the same function using test fixtures in the same way we have been doing so far.

For example, we may write our tests simpley using test fixtures as shown below. Please see the code in file [1_Not_parameterised.cpp](../code/Chapter4/1_Not_parameterised.cpp).

```cpp
class EmployeeTestFixture : public::testing::Test {
    public:
        Employee employee{"John", 25, 8000, 3, 2000};

};

TEST_F(EmployeeTestFixture, NetBonusIsCorrectWhenYearsLessThan10) {
    employee.setNumberYearsEmployed(5);
    EXPECT_EQ(employee.getNetBonus(), 2000);
}

TEST_F(EmployeeTestFixture, NetBonusIsCorrectWhenYearsGreaterThan10) {
    employee.setNumberYearsEmployed(15);
    EXPECT_EQ(employee.getNetBonus(), 3000);
}
```
While the above solution works pretty well, it has a serious drawback. If we carefully look at the tests, we see that the test logic is repeated in both the tests. The only difference between the two tests are the input and output values. Moreover, managing such test will become problematic as the number of test conditions (or input/output) values increases.

An immediate solution that comes to mind to solve this problem is to make use of a loop in C++. For each test, we may use a different input value and expect a different output. Let us see how we can use a loop to solve the same problem as described above. 

The code given below is present in [2_Test_using_for_loop.cpp](../code/Chapter4/2_Test_using_for_loop.cpp).

```cpp
TEST_F(EmployeeTestFixture, NetBonusIsCorrectForDifferentYears) {
    auto input = vector<int>{5, 15};
    auto expected_output = vector<int>{2000, 3000};
    for (int i = 0; i < input.size(); i++) {
        employee.setNumberYearsEmployed(input[i]);
        EXPECT_EQ(employee.getNetBonus(), expected_output[i]);
    }
}
```
Let us try to run this code and see if we get the desired output (shown below).

```bash
[==========] Running 1 test from 1 test suite.
[----------] Global test environment set-up.
[----------] 1 test from EmployeeTestFixture
[ RUN      ] EmployeeTestFixture.NetBonusIsCorrectForDifferentYears
[       OK ] EmployeeTestFixture.NetBonusIsCorrectForDifferentYears (0 ms)
[----------] 1 test from EmployeeTestFixture (0 ms total)

[----------] Global test environment tear-down
[==========] 1 test from 1 test suite ran. (0 ms total)
[  PASSED  ] 1 test.
```

Although, the `for` loop served our purpose and we were able to run our test for multiple values, there is a big problem in this approach. If we carefully look at the output, we can see that both (or multiple values if present) the test cases were combined into a single test. This violates the general rule that we should test only one thing in a test or one assertion per test.

Moroever, the problem gets worse when one of the test fails. In order to understand what happens during a test failure when using a for loop, let us intentionally change the expected output value to an incorrect value. In file, [2_Test_using_for_loop.cpp](../code/Chapter4/2_Test_using_for_loop.cpp), you can make the follwing change.

```cpp
TEST_F(EmployeeTestFixture, NetBonusIsCorrectForDifferentYears) {
    auto input = vector<int>{5, 15};
    auto expected_output = vector<int>{2000, 7000};
    for (int i = 0; i < input.size(); i++) {
        employee.setNumberYearsEmployed(input[i]);
        EXPECT_EQ(employee.getNetBonus(), expected_output[i]);
    }
}
```

On running the code with this change, we get the following output.

```bash
[==========] Running 1 test from 1 test suite.
[----------] Global test environment set-up.
[----------] 1 test from EmployeeTestFixture
[ RUN      ] EmployeeTestFixture.NetBonusIsCorrectForDifferentYears
2_Test_using_for_loop.cpp:21: Failure
Expected equality of these values:
  employee.getNetBonus()
    Which is: 3000
  expected_output[i]
    Which is: 7000
[  FAILED  ] EmployeeTestFixture.NetBonusIsCorrectForDifferentYears (0 ms)
[----------] 1 test from EmployeeTestFixture (0 ms total)

[----------] Global test environment tear-down
[==========] 1 test from 1 test suite ran. (0 ms total)
[  PASSED  ] 0 tests.
[  FAILED  ] 1 test, listed below:
[  FAILED  ] EmployeeTestFixture.NetBonusIsCorrectForDifferentYears

 1 FAILED TEST
```
From the output, we can clearly see that it results in complete failure of the test even though one of the conditions (or test) was right. Moreover, the output does not help much to figure out which test has exactly failed.

The solution for above mentioned issues is to make use of parameterized tests and the next section describes that.

In Google Test, parameterized tests are implemented using the `TEST_P` macro, where "P" stands for parameterized. You define a test class and then specify multiple sets of input data using the `INSTANTIATE_TEST_CASE_P` macro. Each set of input data represents a different instance of the test, and the test framework runs the test case for each instance (more details with example are given in subsequent sections).


---
title: "Parameterised Tests using GoogleTest"
teaching: 30
exercises: 15
questions:
- "What is a parameterised test?"
- "How can I write my own parameterised tests using GoogleTest?"
- "How to use test fixtures with parameterised tests?"
objectives:
- "Understand the need of a parameterised test."
- "Learn how to create a parameterised test using GoogleTest."
- "Appreciate the advantages of parameterised tests."
- "Create a parameterised test based on test fixture to combine the advantages of both."
keypoints:
- "Parameterised tests can be used to repeat a specific test with different inputs, reducing code duplication."
- "Parameterised tests are individual tests, so they are more concise and easy to maintain than using a loop for testing multiple conditions"
- "Fixtures can be combined with parameterised tests for maximum flexibility."
---

## 1. Introduction to Parameterised Tests

**Parameterised tests**, also known as **data-driven tests**, are a feature provided by testing frameworks like Google Test that allows us to write a single test case that can be executed with different sets of test data or inputs. Instead of duplicating similar test cases with slight variations, parameterised tests enable us to define a test once and run it with multiple inputs or test data.

In order to understand the importance of parameterised tests and why we need them, let us consider a very small example. For this chapter, we will be using our `Employee` class that we created in last chapter.

Let us suppose that we want to test that net bonus calculation works fine for different number of years of experience. Remember that our `Employee` class adds an additional bonus of £1000 when an employee has worked for more than 10 years. As a first approach, we might be tempted to write multiple tests for the same function using test fixtures in the same way we have been doing so far.

For example, we may write our tests simply using test fixtures as shown below. Please see the code in file [1_not_parameterised.cpp](https://github.com/ImperialCollegeLondon/unit_testing_Cpp_exercises/tree/main/src/Chapter4/1_not_parameterised.cpp).

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

While the above solution works pretty well, it has a serious drawback. If we carefully look at the tests, we see that the test logic is repeated in both the tests. The only difference between the two tests are the input and output values. Moreover, managing such tests will become problematic as the number of test conditions (or input/output) values increases. Imagine if bonus also depended on productivity, experience, age, etcetera? The number of input variations to test grows exponentially as the number and range of arguments grows.

An immediate solution that comes to mind to solve this problem is to make use of a loop in C++. For each test, we may use a different input value and expect a different output. Let us see how we can use a loop to solve the same problem as described above.

The code given below is present in [2_test_using_for_loop.cpp](https://github.com/ImperialCollegeLondon/unit_testing_Cpp_exercises/tree/main/src/Chapter4/2_test_using_for_loop.cpp).

```cpp
TEST_F(EmployeeTestFixture, NetBonusIsCorrectForDifferentYears) {
    auto input = std::vector<int>{5, 15};
    auto expected_output = std::vector<int>{2000, 3000};
    for (int i = 0; i < input.size(); i++) {
        employee.setNumberYearsEmployed(input[i]);
        EXPECT_EQ(employee.getNetBonus(), expected_output[i]);
    }
}
```

Let us try to run this code and see if we get the desired output (shown below).

~~~
[==========] Running 1 test from 1 test suite.
[----------] Global test environment set-up.
[----------] 1 test from EmployeeTestFixture
[ RUN      ] EmployeeTestFixture.NetBonusIsCorrectForDifferentYears
[       OK ] EmployeeTestFixture.NetBonusIsCorrectForDifferentYears (0 ms)
[----------] 1 test from EmployeeTestFixture (0 ms total)

[----------] Global test environment tear-down
[==========] 1 test from 1 test suite ran. (0 ms total)
[  PASSED  ] 1 test.
~~~
{: .output}

Although, the `for` loop served our purpose and we were able to run our test for multiple values, there is a big problem in this approach. If we carefully look at the output, we can see that both (or multiple values if present) the test cases were combined into a single test. This violates the general rule that we should test only one thing in a test or one assertion per test.

Moreover, the problem gets worse when one of the tests fails. In order to understand what happens during a test failure when using a for loop, let us intentionally change the expected output value to an incorrect value. In file, [2_test_using_for_loop.cpp](https://github.com/ImperialCollegeLondon/unit_testing_Cpp_exercises/tree/main/src/Chapter4/2_test_using_for_loop.cpp), you can make the following change.

```cpp
TEST_F(EmployeeTestFixture, NetBonusIsCorrectForDifferentYears) {
    auto input = std::vector<int>{5, 15};
    auto expected_output = std::vector<int>{2000, 7000};
    for (int i = 0; i < input.size(); i++) {
        employee.setNumberYearsEmployed(input[i]);
        EXPECT_EQ(employee.getNetBonus(), expected_output[i]);
    }
}
```

On running the code with this change, we get the following output.

~~~
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
~~~
{: .output}

From the output, we can clearly see that it results in complete failure of the test even though one of the conditions (or tests) was right. Moreover, the output does not help much to figure out which test has failed.

The solution to these issues is to make use of parameterised tests and the next section describes that.

## 2. Parameterised tests in GoogleTest

In Google Test, parameterised tests are implemented using the `TEST_P` macro, where "P" stands for parameterised. We define a test class and then specify multiple sets of input data using the `INSTANTIATE_TEST_CASE_P` macro. Each set of input data represents a different instance of the test, and the test framework runs the test case for each instance.

A parameterized tests in GoogleTest requires the following components in general.

1. **A parameterised test class**: Similar to the process of a test fixture, we need to create a class derived from `testing::TestWithParam<T>` where `T` could be any valid C++ type.

```cpp
class YourTestParameterisedClass : public::TestWithParam<T> {
    public:
        ClassUnderTest publicInstance;
};
```

2. **Data structure to hold your values**: We need to create some data structure to store our values (both input and output). We can use a `struct` for this purpose as shown below.

```cpp
struct MyStruct{
    int input;
    int output;
    
    //construtor of values struct
    MyStruct(int in, int out) : input(in), output(out) {}
};
```

Once you have defined a structure to hold your values, you can create an instance of it with the actual set of input and output values as shown below.

```cpp
MyStruct MyValues[] = {
    MyStruct{InputVal1, OutputVal1},  //using constructor to create an instance of MyStruct.  
    MyStruct{InputVal2, OutputVal2}
};
```

3. **Create your test with TEST_P macro**: Instead of `TEST_F` macro that we used for test fixture, we use a `TEST_P` macro where `P` stands for `Parameterised` as shown below.

```cpp
TEST_P(YourTestParameterisedClass, NameofTest) {
    // Test logic goes here.
}
```

4. **Instantiate your test**: Finally, we instantiate our test by using the `INSTANTIATE_TEST_SUITE_P` macro. The general syntax of this macro is given below.

```cpp
INSTANTIATE_TEST_SUITE_P(SuitableNameTest,
                         YourTestParameterisedClass,
                         ValuesIn(MyValues));
```

In the above cell, the first argument to `INSTANTIATE_TEST_SUITE_P` could be any suitable name. GoogleTest will add this as a PREFIX to the test name when you will run the test. The second argument is the name of the parameterised class that you have created, which is also the first argument for `TEST_P` macro. Finally, the last argument is a `ValuesIn()` function which is defined in the GoogleTest library. It helps to inject the test values into the parameterised test one by one.

Let us see how we use the above concepts for an actual test that we have been writing in our previous subsections. For more details, please see [3_parameterised_not_using_fixture.cpp](https://github.com/ImperialCollegeLondon/unit_testing_Cpp_exercises/tree/main/src/Chapter4/3_parameterised_not_using_fixture.cpp).

```cpp
// Create a structure that holds the input and output values.
// This structure is used to inject values into the test.
struct TestValues{
    int input;
    int output;
    
    //constructor of values struct
    TestValues(int in, int out) : input(in), output(out) {}
};

// Create a parameterised class by deriving from testing::TestWithParam<T> where T could be any valid C++ type.
class EmployeeTestParameterised : public::testing::TestWithParam<TestValues> {
    public:
        Employee employee{"John", 25, 8000, 3, 2000};
};

// Create an array of values (of type TestValues) to be injected into the test.
TestValues values[] = {
    TestValues{5, 2000},
    TestValues{15, 3000}
};

//Test net bonus works fine for different number of years.
TEST_P(EmployeeTestParameterised, NetBonusIsCorrectForDifferentYears) {
    TestValues current_test_case_value = GetParam();
    employee.setNumberYearsEmployed(current_test_case_value.input);
    EXPECT_EQ(employee.getNetBonus(), current_test_case_value.output);
}

// Instantiate the test case with the values array.
INSTANTIATE_TEST_SUITE_P( NetBonusIsCorrectForDifferentYears, 
                         EmployeeTestParameterised,
                         testing::ValuesIn(values));
```

On running the above file, we see the following output.

~~~
[==========] Running 2 tests from 1 test suite.
[----------] Global test environment set-up.
[----------] 2 tests from NetBonusIsCorrectForDifferentYears/EmployeeTestParameterised
[ RUN      ] NetBonusIsCorrectForDifferentYears/EmployeeTestParameterised.NetBonusIsCorrectForDifferentYears/0
[       OK ] NetBonusIsCorrectForDifferentYears/EmployeeTestParameterised.NetBonusIsCorrectForDifferentYears/0 (0 ms)
[ RUN      ] NetBonusIsCorrectForDifferentYears/EmployeeTestParameterised.NetBonusIsCorrectForDifferentYears/1
[       OK ] NetBonusIsCorrectForDifferentYears/EmployeeTestParameterised.NetBonusIsCorrectForDifferentYears/1 (0 ms)
[----------] 2 tests from NetBonusIsCorrectForDifferentYears/EmployeeTestParameterised (0 ms total)

[----------] Global test environment tear-down
[==========] 2 tests from 1 test suite ran. (0 ms total)
[  PASSED  ] 2 tests.
~~~
{: .output}

In this output, there are two things worth noting:-

1. As expected, we are now running two tests as compared to just one in the case of a `for` loop.
2. The test name `NetBonusIsCorrectForDifferentYears/EmployeeTestParameterised.NetBonusIsCorrectForDifferentYears/0` is a combination of the following:-
    - A Prefix `NetBonusIsCorrectForDifferentYears` coming from INSTANTIATE_TEST_SUITE_P.
    - Parameterised class name `EmployeeTestParameterised` coming from the first argument of `TEST_P` macro.
    - Test name `NetBonusIsCorrectForDifferentYears` coming from the second argument of `TEST_P` macro.
    - Finally, the iteration number.

With this parameterised test, we were able to solve the issues that we were discussing above. However, in doing so, we changed the test fixture and converted it to use `TEST_P` macro. Our previous tests based on `TEST_F` macro will not work anymore as it has been replaced. The important question is: What shall we do so that we can still keep all our useful tests from test fixtures while still being able to add parameterised test? The solution is to combine test fixtures with parameterised tests and the next subsection explains that.

> ## Exercise 1: Parameterised tests for Non member functions (i.e. functions which are not part of any class)
>
> Consider that you have a simple function `int Sum(int a, int b)` that takes in two integer values `a` and `b` and returns their sum. Write a parameterised test for this function using GoogleTest. Please feel free to use Google to search how to write parameterised tests for non member functions.
>
> > ## Solution
> >
> > The full solution is given in [Solution](https://github.com/ImperialCollegeLondon/unit_testing_Cpp_exercises/tree/main/src/Chapter4/Exercise_solutions/a_param_test_normal_function.cpp). We present some important parts of the solution below.
> >
> > ```cpp
> > // Define a test fixture class
> > class ParameterizedTest : public testing::TestWithParam<std::pair<int, int>> {
> > };
> > 
> > // Define the test case with the parameterized test
> > TEST_P(ParameterizedTest, TestSum) {
> >     // Get the parameter values
> >     int a = GetParam().first;
> >     int b = GetParam().second;
> > 
> >     // Call your normal function
> >     int result = Sum(a, b);
> > 
> >     // Perform assertion
> >     ASSERT_EQ(a + b, result);
> > }
> > 
> > // Define the test data
> > INSTANTIATE_TEST_SUITE_P(Default, ParameterizedTest, testing::Values(
> >     std::make_pair(1, 1),
> >     std::make_pair(2, 3),
> >     std::make_pair(-5, 10)
> > ));
> > ```
> >
> {: .solution}
>
{: .challenge}

> ## Exercise 2: Multiple parameterised tests
>
> Suppose you have the following 3 functions that you want to test using parameterised tests:-
>
> 1. `int Sum(int a, int b)` as defined in the previous exercise,
>
> 2. `double Multiply(double a, double b)` function which multiples the two numbers and
>
> 3. `double Power(double a, int b)` function which raises a number `a` to an integer power `b`.
>
> For the sake of simplicity, assume that you can use the same parameters for your `Multiply` function as you have used in your `Sum` function. However, for the `Power` function, the parameters are different. Write a parameterised test for all the three functions.
>
> > ## Solution
> >  
> > Although we are testing 3 parameterised functions, we do not have to add 3 `INSTANTIATE_TEST_SUITE_P` macros in our code. This is because an `INSTANTIATE_TEST_SUITE_P` macro looks for the test suite name (2nd argument) and if it is same, it will instantiate the tests for all of them.  Therefore, in our current exercise, we can use the same `INSTANTIATE_TEST_SUITE_P` for `Add` and `Multiply` functions while we can use a different `INSTANTIATE_TEST_SUITE_P` for the `Power` function.
> >
> > We provide some portion of solution code below. Full code can be found in [Solution](https://github.com/ImperialCollegeLondon/unit_testing_Cpp_exercises/tree/main/src/Chapter4/Exercise_solutions/b_multiple_test_p_instant.cpp)
> >
> > ```cpp
> > // Define the test case with the parameterized test for multiply function.
> > TEST_P(ParameterizedTest, TestMultiply) {
>>     // Your test logic goes here.
> > }
> > 
> > // Define a test fixture class
> > class ParameterizedTest_Power : public testing::TestWithParam<std::tuple<double, int, double>> {
> > };
> > 
> > //Check if the power function works fine for different values of a and b
> > TEST_P(ParameterizedTest_Power, TestPowerFun){
> >     // Get the parameter values
> >     double a = std::get<0>(GetParam());
> >     int b = std::get<1>(GetParam());
> >     double answer = std::get<2>(GetParam());
> > 
> >     // Call your normal function
> >     double result = Power(a, b);
> > 
> >     // Perform assertion
> >     ASSERT_DOUBLE_EQ(answer, result);
> > }
> > 
> > // Define the test data
> > INSTANTIATE_TEST_SUITE_P(PowTest, ParameterizedTest_Power, testing::Values(
> >     std::make_tuple(1, 1, 1),
> >     std::make_tuple(2, 3, 8),
> >     std::make_tuple(2.5, 2, 6.25)
> > ));
> > ```
> >
> {: .solution}
>
{: .challenge}

## 3. Parameterised test based on test fixture

In order to create a parameterised test from a test fixture, all we need to do is to create a parameterised test class which derives from both the test fixture class and `testing::WithParamInterface<T>` class (defined in GoogleTest) to create parameterised tests.

```cpp
// create a parameterised test class from the fixture defined above.
class YourParameterisedClass : public YourFixtureClass,
                               public WithParamInterface<T> {
};
```

For the purpose of demonstration, let us assume that we now want to check our tax calculation function `getTaxAmount()` which has more branches as compared to bonus calculation. For complete code, see the file [4_param_test_based_fixture.cpp](https://github.com/ImperialCollegeLondon/unit_testing_Cpp_exercises/tree/main/src/Chapter4/4_param_test_based_fixture.cpp). We give a small section of code below for reference.

```cpp
// Create a test fixture.
class EmployeeTestFixture : public::testing::Test {
    public:
        Employee employee{"John", 25, 8000, 5, 1000};

};

// Create a structure that holds the input and output values.
// This structure is used to inject values into the test.
struct TestValues{
    double inp_salary;
    double inp_bonus;
    double inp_years_employed;
    double out_tax;
    
    //constructor of values struct
    TestValues(double salary, double bonus, double years_employed, double tax) 
              : inp_salary(salary), 
                inp_bonus(bonus), 
                inp_years_employed(years_employed), 
                out_tax(tax) {}
};

// create a parameterised test class from the fixture defined above.
class EmployeeTestParameterisedFixture : public EmployeeTestFixture, 
                                         public testing::WithParamInterface<TestValues> {
};

// Create an array of values (of type TestValues) to be injected into the test.
TestValues values[] = {
    // value are in format: salary, basic_bonus, years_employed, tax
    TestValues{8000, 2000, 3, 0},
    TestValues{8000, 2000, 11, 100},
    TestValues{60000, 8000, 13, 16500}
};

// Test that the tax calculation is correct.
TEST_P(EmployeeTestParameterisedFixture, TaxCalculationIsCorrect) {
    TestValues current_test_case_value = GetParam();
    employee.setBaseSalary(current_test_case_value.inp_salary);
    employee.SetBasicBonus(current_test_case_value.inp_bonus);
    employee.setNumberYearsEmployed(current_test_case_value.inp_years_employed);
    EXPECT_EQ(employee.getTaxAmount(), current_test_case_value.out_tax);
}

// Instantiate the test case with the values array.
INSTANTIATE_TEST_SUITE_P( CheckTaxCalculation, 
                          EmployeeTestParameterisedFixture,
                          testing::ValuesIn(values));
```

The major change as compared to our previous example is shown in the cell below and this change is responsible for generating a parameterised test using a test fixture.

```cpp
class EmployeeTestParameterisedFixture : public EmployeeTestFixture, 
                                         public WithParamInterface<TestValues> {
};
```

In addition, we used a function `GetParam()` defined in `gtest.h`. This function can help us to get the input values passed via `ValuesIn()` function and use it in the test logic according to our requirements. In this case, it helps us to retrieve 4 values in the order `inp_salary`, `inp_bonus`, `inp_years_employed` and `out_tax` for each test case. Thus, `GetParam()` provides a convenient way to retrieve multiple values and use them in our test logic.

## 4. Advantages of Parameterised tests

From the above discussion, we can see that the parameterised tests have the following advantages.

1. **Code Reusability**: With parameterised tests, we can write a single test case that can be executed with different inputs or test data. This promotes code reusability by eliminating the need to duplicate similar test cases. Instead, we can define the test logic once and apply it to multiple scenarios, reducing code duplication and improving maintainability.

2. **Increased Test Coverage**: Parameterised tests allow us to easily test a wide range of input values or test cases without writing separate test cases for each variation. This enables us to achieve better test coverage by covering various combinations, edge cases, and boundary values in a concise manner.

3. **Simplified Test Maintenance**: When changes are required in the test logic, having parameterised tests simplifies the maintenance process. Instead of modifying multiple test cases individually, we only need to update the single test case, which will automatically be executed with the new test data. This saves time and effort in maintaining and updating the tests.

4. **Simplified Test Reporting**: Parameterised tests provide a concise way to report test results for multiple test cases. Each instance of the parameterised test is reported individually, allowing us to identify which specific inputs or test data passed or failed. This facilitates quick identification and debugging of issues.

### Summary

In this chapter, we learnt about the basics of parameterised tests and how to use them in GoogleTest. We also learnt how to combine test fixture with parameterised tests. Finally, we learnt the advantages of parameterised tests.

{% include links.md %}

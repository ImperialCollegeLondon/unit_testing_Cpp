#include <iostream>
#include <gtest/gtest.h>
#include "employee.h"

using namespace :: testing;
using namespace :: std;

// Create a structure that holds the input and output values.
// This structure is used to inject values into the test.
struct TestValues{
    int input;
    int output;
    
    //construtor of values struct
    TestValues(int in, int out) : input(in), output(out) {}
};

// Create a parameterised class by deriving from testing::TestWithParam<T> where T could be any valid C++ type.
class EmployeeTestParameterised : public::TestWithParam<TestValues> {
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
                         ValuesIn(values));

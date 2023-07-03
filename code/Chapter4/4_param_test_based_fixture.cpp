#include <iostream>
#include <gtest/gtest.h>
#include "employee.h"

using namespace :: testing;
using namespace :: std;

// Create a test fixture.
class EmployeeTestFixture : public::testing::Test {
    public:
        Employee employee{"John", 25, 8000, 5, 1000};

};

// Test if we can set the name of an employee.
TEST_F(EmployeeTestFixture, CanSetName) {
    employee.setName("John Doe");
    EXPECT_EQ(employee.getName(), "John Doe");
}

// Test that the name cannot be empty.
TEST_F(EmployeeTestFixture, NameCannotBeEmpty) {
    EXPECT_THROW(employee.setName(""), invalid_argument);
}

// Test if we can set the age of an employee.
TEST_F(EmployeeTestFixture, CanSetAge) {
    employee.setAge(30);
    EXPECT_EQ(employee.getAge(), 30);
}

// Create a structure that holds the input and output values.
// This structure is used to inject values into the test.
struct TestValues{
    double inp_salary;
    double inp_bonus;
    double inp_years_employed;
    double out_tax;
    
    //construtor of values struct
    TestValues(double salary, double bonus, double years_employed, double tax) 
              : inp_salary(salary), 
                inp_bonus(bonus), 
                inp_years_employed(years_employed), 
                out_tax(tax) {}
};

// create a parameterised test class from the fixture defined above.
class EmployeeTestParameterisedFixture : public EmployeeTestFixture, 
                                       public WithParamInterface<TestValues> {
};

// Create an array of values (of type TestValues) to be injected into the test.
TestValues values[] = {
    // value are in format: salary, basic_bonus, years_employed, tax
    TestValues{8000, 2000, 3, 0},
    TestValues{8000, 2000, 11, 100},
    TestValues{15000, 3000, 4, 800},
    TestValues{26000, 4000, 12, 3200},
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
                          ValuesIn(values));
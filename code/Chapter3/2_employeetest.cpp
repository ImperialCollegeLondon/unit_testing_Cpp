#include <gtest/gtest.h>
#include "employee.h"

// Create a test fixture.
class EmployeeTestFixture : public::testing::Test {
    public:
        Employee employee{"John", 25, 45000, 12, 5000};

};

// Test if we can set the name of an employee.
TEST_F(EmployeeTestFixture, CanSetName) {
    employee.setName("John Doe");
    EXPECT_EQ(employee.getName(), "John Doe");
}

// Test that the name cannot be empty.
TEST_F(EmployeeTestFixture, NameCannotBeEmpty) {
    EXPECT_THROW(employee.setName(""), std::invalid_argument);
}

// Test if we can set the age of an employee.
TEST_F(EmployeeTestFixture, CanSetAge) {
    employee.setAge(30);
    EXPECT_EQ(employee.getAge(), 30);
}

//Test that the tax calculation is correct.
TEST_F(EmployeeTestFixture, TaxCalculationIsCorrect) {
    EXPECT_EQ(employee.getTaxAmount(), 7500);
}


// Check that the net salary is correct.
TEST_F(EmployeeTestFixture, NetSalaryIsCorrect) {
    EXPECT_EQ(employee.getNetSalary(), 43500);
}

#include <gtest/gtest.h>
#include "employee.h"

// Create a test fixture.
class EmployeeTestFixture : public::testing::Test {
    public:
        Employee employee{"John", 25, 8000, 3, 2000};

};

// Test net bonus when number of years is less than 10.
TEST_F(EmployeeTestFixture, NetBonusIsCorrectWhenYearsLessThan10) {
    employee.setNumberYearsEmployed(5);
    EXPECT_EQ(employee.getNetBonus(), 2000);
}

// Test net bonus when number of years is greater than 10.
TEST_F(EmployeeTestFixture, NetBonusIsCorrectWhenYearsGreaterThan10) {
    employee.setNumberYearsEmployed(15);
    EXPECT_EQ(employee.getNetBonus(), 3000);
}


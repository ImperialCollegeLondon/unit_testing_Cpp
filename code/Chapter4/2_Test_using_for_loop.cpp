#include <gtest/gtest.h>
#include "employee.h"

// Create a test fixture.
class EmployeeTestFixture : public::testing::Test {
    public:
        Employee employee{"John", 25, 8000, 3, 2000};

};

// Test net bonus works fine for different number of years.
TEST_F(EmployeeTestFixture, NetBonusIsCorrectForDifferentYears) {
    auto input = std::vector<int>{5, 15};
    auto expected_output = std::vector<int>{2000, 3000};
    for (int i = 0; i < input.size(); i++) {
        employee.setNumberYearsEmployed(input[i]);
        EXPECT_EQ(employee.getNetBonus(), expected_output[i]);
    }
}
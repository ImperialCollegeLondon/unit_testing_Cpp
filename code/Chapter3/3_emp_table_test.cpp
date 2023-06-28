#include <iostream>
#include <gtest/gtest.h>
#include "employee_table.h"

using namespace :: testing;
using namespace :: std;

// Test fixture for EmployeeTable class.
class EmployeeTableTest : public testing::Test {
    public:
        EmployeeTable table;
};

// Test that the table is empty when created.
TEST_F(EmployeeTableTest, TableIsEmptyWhenCreated) {
    EXPECT_TRUE(table.isEmpty());
}
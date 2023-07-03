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


// Test that table has size zero when created.
TEST_F(EmployeeTableTest, TableHasSizeZeroWhenCreated) {
    EXPECT_EQ(table.getEntryCount(), 0);
}

// Test that the table is not empty after adding an employee.
TEST_F(EmployeeTableTest, TableIsNotEmptyAfterAddingEmployee) {
    Employee new_employee("John Doe", 30, 5000, 5, 1000);
    table.addEmployee(new_employee);
    EXPECT_FALSE(table.isEmpty());
}

// Test that number of entries is one after adding an employee.
TEST_F(EmployeeTableTest, NumberOfEntriesIsOneAfterAddingEmployee) {
    Employee new_employee("John Doe", 30, 5000, 5, 1000);
    table.addEmployee(new_employee);
    EXPECT_EQ(table.getEntryCount(), 1);
}

// Test that number of entries in table reduces by one after removing an employee.
TEST_F(EmployeeTableTest, NumberOfEntriesIsOneLessAfterRemovingEmployee) {
    Employee new_employee("John Doe", 30, 5000, 5, 1000);
    table.addEmployee(new_employee);
    table.removeEmployee("John Doe");
    EXPECT_EQ(table.getEntryCount(), 0);
}
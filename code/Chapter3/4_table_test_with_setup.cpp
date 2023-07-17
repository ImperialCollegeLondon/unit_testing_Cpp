#include <gtest/gtest.h>
#include "employee_table.h"

// Test fixture for EmployeeTable class.
class EmployeeTableTest : public testing::Test {
    public:
        EmployeeTable table;
};

TEST_F(EmployeeTableTest, TableIsEmptyWhenCreated) {
    EXPECT_TRUE(table.isEmpty());
}

TEST_F(EmployeeTableTest, TableHasSizeZeroWhenCreated) {
    EXPECT_EQ(table.getEntryCount(), 0);
}


class EmployeeTableWithOneEmployee : public testing::Test {
    public:
        EmployeeTable table;
        Employee* employee;

        void SetUp() override {
            employee = new Employee("John Doe", 30, 5000, 5, 1000);
            table.addEmployee(*employee);
        }

        void TearDown() override {
            delete employee;
            employee = nullptr;
        }
};


TEST_F(EmployeeTableWithOneEmployee, TableIsNotEmptyWhenCreatedWithOneEmployee) {
    EXPECT_FALSE(table.isEmpty());
}


TEST_F(EmployeeTableWithOneEmployee, NumberOfEntriesIsOneWhenCreatedWithOneEmployee) {
    EXPECT_EQ(table.getEntryCount(), 1);
}


TEST_F(EmployeeTableWithOneEmployee, NumberOfEntriesIsOneLessAfterRemovingEmployee) {
    table.removeEmployee("John Doe");
    EXPECT_EQ(table.getEntryCount(), 0);
}
#include <gtest/gtest.h>
#include "employee.h"



// Test if we can set the name of an employee.
TEST(EmployeeTest, CanSetName) {
    Employee employee{"John", 25, 10000, 5, 1000};
    employee.setName("John Doe");
    EXPECT_EQ(employee.getName(), "John Doe");
}

// Test if we can set the age of an employee.
TEST(EmployeeTest, CanSetAge) {
    Employee employee{"John", 25, 10000, 5, 1000};
    employee.setAge(30);
    EXPECT_EQ(employee.getAge(), 30);
}


#include <iostream>
#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "employee_table.h"

class MockEmployee
{
public:
    MOCK_METHOD(void, setBasicBonus, (double));
};

TEST(EmployeeTableTest, SetBasicBonusForEveryone)
{
    EmployeeTable<MockEmployee> table{EmployeeTable<MockEmployee>()};
    double newBonus{2000};
    MockEmployee employee1{MockEmployee{}};
    MockEmployee employee2{MockEmployee{}};

    EXPECT_CALL(employee1, setBasicBonus(newBonus)).Times(1);
    EXPECT_CALL(employee2, setBasicBonus(newBonus)).Times(1);

    table.addEmployee(employee1);
    table.addEmployee(employee2);
    table.bumpSalaryBonus(newBonus);
};

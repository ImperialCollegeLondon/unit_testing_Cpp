#include <iostream>
#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "employee_table.h"

class MockEmployee
{
public:
    MOCK_METHOD(void, setIncreasedBasicBonus, (double));
};

TEST(EmployeeTableTest, SetBasicBonusForEveryone)
{
    EmployeeTable<MockEmployee> table; 
    double newBonus{2000};
    
    MockEmployee employee1;
    MockEmployee employee2;

    // Important Note 1
    // As per the google mock documentation, the EXPECT_CALL() macro should be 
    // set (i.e. expectations should be defined) before passing the mock objects
    // to the API or code under test.
    // Link:- http://google.github.io/googletest/gmock_for_dummies.html#using-mocks-in-tests
    EXPECT_CALL(employee1, setIncreasedBasicBonus(newBonus)).Times(1);
    EXPECT_CALL(employee2, setIncreasedBasicBonus(newBonus)).Times(1);

    // Important Note 2
    // A mock object cannot be directly copied to a vector because of the way the copy constructor is 
    // defined for a mock class. 
    // Instead pointer can be used to add the mock objects to the vector.
    // Link:- https://github.com/google/googletest/issues/3734
    table.addEmployee(&employee1);
    table.addEmployee(&employee2);

    // This is the function under test.
    table.bumpSalaryBonus(newBonus);
};

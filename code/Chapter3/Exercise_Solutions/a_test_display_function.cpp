#include <gtest/gtest.h>
#include "employee_table.h"

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


// Check the display function work correctly.
TEST_F(EmployeeTableWithOneEmployee, DisplayFunctionWorksCorrectly) {

    // STEP 1: ARRANGE
    std::stringstream s_input;

    // STEP 2: ACT
    // You would use the following line in your application (production use) to display the employees' names on the screen.
    // However, this line is not necessary for the test and has been introduced only for the demonstration purpose.
    table.displayEmployeesName(std::cout); 

    // Pass a string stream object to the function under test instead of std::cout. 
    // Later we will use it to compare with the expected output.
    table.displayEmployeesName(s_input);    
    
    // Store expected output in a string.
    std::string expected_output = "-------------------------------------------------- \n"
                                  "John Doe\n"
                                  "-------------------------------------------------- \n";

    // STEP 3: ASSERT
    EXPECT_EQ(s_input.str(), expected_output);
}

// Compilation command when using g++ compiler:
// g++ a_test_display_function.cpp employee.cpp employee_table.cpp  -lgtest -lgtest_main -lpthread -o test
---
title: "Introduction to Test Fixtures using GoogleTest"
teaching: 30
exercises: 15
questions:
- "What is a test fixture?"
- "How can I create my own test fixture using GoogleTest?"
- "What do Setup and Teardown mean in relation to test fixtures?"
objectives:
- "Understand the basics of test fixtures."
- "Write some test fixtures using GoogleTest."
- "Analyze the advantages of test fixtures."
- "Learn why we need Setup and Teardown functions."
- "Create your own Setup and Teardown functions."
- "Learn how to run a subset of tests."
keypoints:
- "A test fixture is a useful tool while writing unit tests because it reduces the code duplication, maintains test independence and takes care of the common setup and teardown operations."
- "Test fixture ensures that different tests do not interfere with each other by creating a new instance of its fixture class for every test."
- "GoogleTest allows us to run a subset of tests which can be quite useful if our full test suite takes a long time to run or if we want to develop and check the functionality of a particular test."  
---
## 1. Brief Introduction of Test Fixtures

A test fixture, in the context of unit testing, refers to the preparation and configuration needed to run a set of test cases. It includes the setup of the test environment, the creation of necessary objects or resources, and the cleanup steps after the tests are executed. Test fixtures help ensure that the tests are performed in a controlled and consistent environment, providing reliable and reproducible results.

In GoogleTest, a test fixture is implemented using a test fixture class. This class serves as a container for shared setup and cleanup logic, as well as any shared objects or resources required by the test cases within the fixture.

### 1.1 When is a Test Fixture Needed?

A test fixture is typically used in the following scenarios:

1. **Shared Setup and Teardown**: When multiple test cases require identical preparation (Setup) and cleanup (Teardown), a test fixture is beneficial. Instead of duplicating the setup and teardown code in each test case, we can define it once in the test fixture and reuse it across all the tests.

2. **Reducing Code Duplication**: Test fixtures help in reducing code duplication. By encapsulating the common setup and teardown logic within a fixture, we avoid duplicating the same code in multiple test cases. This improves code maintainability and reduces the chances of errors due to inconsistent or incomplete setup/teardown.

3. **Isolation and Independence**: Test fixtures provide a level of isolation and independence for each test case. Each test case within a fixture runs in its own instance of the fixture class, ensuring that changes made by one test case do not affect the others. This allows for parallel execution of test cases without interference.

Let us understand how to create a test fixture, setup and teardown functions with examples.

## 2. Problem under consideration for testing

In order to create our own test fixture, we will first explain the context or problem that we are trying to solve. We will be adding tests to check that our code works as intended by making use of test fixtures.

Consider that you want to write a program to manage the details of an employee. The program should allow you to add basic details of an employee such as:

1. Name
2. Age
3. Basic Salary
4. Number of years of employment
5. Basic Bonus the employee has received in this year.

The program should calculate the Net Bonus, Tax and Salary based on the following rules:

1. Bonus Rule: An employee gets an additional £1000 bonus if she or he has worked for more than 10 years.
2. Tax Rule: Tax is calculated on a combination of basic salary and net bonus as shown below.

    * `0` if salary is less than `10k` GBP.
    * `10%` for salary between `10K-20K` GBP.
    * `20%` for salary between `20K-50K` GBP
    * `50%` for salary greater than `50K` GBP

Based on above, we can declare the employee class in `employee.h` as shown below ([Declaration of Employee class](https://github.com/ImperialCollegeLondon/unit_testing_Cpp_exercises/tree/main/src/Chapter3/employee.h)).

```cpp
class Employee
{
private:
    std::string name;
    float age;
    double base_salary; //salary before calculating tax and adjusting bonus.
    double number_years_employed;

    double basic_bonus; //bonus for current year.
    double net_bonus; //bonus after adjusting for experience.
    
    double tax_amount;
    double net_salary; //salary after calculating tax and adjusting bonus.

public:
    // Constructor.
    Employee(const std::string& employee_name, float employee_age, 
             double employeeSalary, double employeeNumberYearsEmployed,
             double employeeBonus);

    // Public member functions to set values.
    void setName(const std::string& employee_name); 
    void setAge(float employee_age) ;
    void setBaseSalary(double employeeSalary); 
    void setNumberYearsEmployed(double employeeNumberYearsEmployed); 
    void SetBasicBonus(double employeeBonus);

    void calcNetBonus(); //To calculate net bonus while considering experience.
    void calcTaxAmount(); // To calculate tax to be paid based on salary with bonus
    void calcNetSalary(); // To calculate net salary after adjusting tax and bonus.

    // Getter functions.
    std::string getName() const;
    float getAge() const;
    double getBasicSalary() const;
    double getNumberYearsEmployed() const;
    double getBasicBonus() const;
    double getNetBonus() const;
    double getTaxAmount() const;
    double getNetSalary() const;

    void displayInfo() const;

    // Destructor
    ~Employee();
};
```

For the definition part, we include only a few functions here. You can find the complete definition of this class in [employee.cpp](https://github.com/ImperialCollegeLondon/unit_testing_Cpp_exercises/tree/main/src/Chapter3/employee.cpp).

```cpp
Employee::Employee(const std::string& employee_name, float employee_age,
                   double employeeSalary, double employeeNumberYearsEmployed,
                   double employeeBonus)
                    : age(employee_age),
                      base_salary(employeeSalary),
                      number_years_employed(employeeNumberYearsEmployed),
                      basic_bonus(employeeBonus),
                      net_bonus(0),
                      tax_amount(0),
                      net_salary(0)
{
    setName(employee_name);
    calcNetBonus();
    calcTaxAmount();
    calcNetSalary();

}

void Employee::setName(const std::string& employee_name) 
{
    if(employee_name == "")
    {
        throw std::invalid_argument("Name cannot be empty");
    }
    name = employee_name;
}

void Employee::setAge(float employee_age) 
{
    age = employee_age;
}
```

With this code, we now have the necessary fragments to test our `Employee` class. Let us see this in action.

## 3. Unit tests for our employee class without test fixtures

In order to clearly demonstrate why a test fixture would be needed, we first write some tests for our employee class without using a fixture. This will help us to understand why does a fixture is useful and how to use it.

For this subsection, let us assume that we are checking two functionalities of our employee class (for code, please see [1_employeetest.cpp](https://github.com/ImperialCollegeLondon/unit_testing_Cpp_exercises/tree/main/src/Chapter3/1_employeetest.cpp)) which are:-

1. We can set the name of employee correctly.
2. We can set the age correctly.

The code for these two tests (which is entirely based on what we learn in second module of this course) is given below.

```cpp
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
```

While the above test solve our problem, there is a problem of code duplication and object creation for each test. As we can see in each test that we have to create an instance of employee class by using the statement `Employee employee{"John", 25, 10000, 5, 1000};`. This is against the `DRY (Don't Repeat Yourself)' https://en.wikipedia.org/wiki/Don%27t_repeat_yourself principle.

Moreover, all our tests depend on the same `Employee` class. It therefore makes sense to create an instance of `Employee` once, and let the GoogleTest manage the creation of the instance for each test case. Let us see this in action in next section.

## 4. Test fixture for our employee class

Now that we know why do we need a test fixture, let us fist learn about the basic syntax of the test fixture in GoogleTest and then write the code for it.

In GoogleTest, a test fixture is created by writing another class which is derived from `::testing::Test` using `public` [access specifier](https://en.cppreference.com/w/cpp/language/access). The general syntax is as shown below

```cpp
class Your_test_fixture_class_name : public::testing::Test {
    public:
        ClassUnderTest publicInstance;

    protected:
        ClassUnderTest protectedInstance;

    private:
        ClassUnderTest privateInstance;
};
```

Please note that you do not need to use all three access specifiers `public`, `private` and `protected`  defined above. The choice would depend on the following:-

1. **public**: This is the most commonly used access specifier in test fixtures. It allows the test fixture class and its members (including the instance of the class we want to test) to be accessed from anywhere, including test cases defined outside the fixture class.

2. **protected**: This access specifier restricts the visibility of the test fixture class and its members to derived classes and other classes within the same hierarchy. It can be useful if we have derived test fixture classes that need access to the class under test or if we want to limit the accessibility of the test fixture within a certain scope.

3. **private**: This access specifier restricts the visibility of the test fixture class and its members only to the test fixture class itself. It can be useful if we want to encapsulate the test logic within the test fixture class and prevent external access or if we want to limit the scope of the test fixture.

For our course, we will be using the `public` access specifier. Once we have the test fixture class, we use the `TEST_F` macro available in GoogleTest to write our tests instead of the `TEST` macro we have been using so far. The general syntax is given below.

```cpp
TEST_F(Your_test_fixture_class_name, Your_test_name) {
    // Test logic goes here
}
```

Since we now have all the basic tools to create our own test fixtures, let us rewrite the above tests using a fixture. The code is present in this [2_employeetest.cpp](https://github.com/ImperialCollegeLondon/unit_testing_Cpp_exercises/tree/main/src/Chapter3/2_employeetest.cpp). For reference, the tests are shown in the cell below.

```cpp
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

// Test if we can set the age of an employee.
TEST_F(EmployeeTestFixture, CanSetAge) {
    employee.setAge(30);
    EXPECT_EQ(employee.getAge(), 30);
}
```

## 5. Why do we need setup and teardown in test fixture?

So far, our test fixture class only creates an instance of object for the class under test. In many cases, we often want some common action for all our tests such as adding an entry, connection to a database, response from a site etc. Let us try to understand this with example which will set the background for the `setup` and `teardown` functions.

Let us consider that we are creating a table which will store the details of various employees. The table allows us to add new entries, remove employees from the table, get the number of entries in the table etc. The declaration of table class is given in [employee_table.h](https://github.com/ImperialCollegeLondon/unit_testing_Cpp_exercises/tree/main/src/Chapter3/employee_table.h). The definitions of table class is present in [employee_table.cpp](https://github.com/ImperialCollegeLondon/unit_testing_Cpp_exercises/tree/main/src/Chapter3/employee_table.cpp). We give the list of functions in the table class for reference below.

```cpp
// Member function to add employees into the table.
void addEmployee(const Employee& employee);

// Member function to remove employees into the table.
void removeEmployee(const std::string& employeeName);

// Member function to display information (names) of all employees in the table.
void displayEmployeesName() const;

// Function to check if the table is empty.
bool isEmpty() const;

// Function to get the number of entries in the table.
int getEntryCount() const;
```

We want to test our table class. In particular, we are interested in testing the following:

1. Table is not empty after adding an employee.
2. Number of entries is one after adding an employee.
3. Number of entries in table reduces by one after removing an employee (assuming that there was at least one entry in the table).

Using our knowledge of test fixtures learnt in previous subsection, we can write the tests as shown below. Please see the file [3_emp_table_test.cpp](https://github.com/ImperialCollegeLondon/unit_testing_Cpp_exercises/tree/main/src/Chapter3/3_emp_table_test.cpp) for more details.

```cpp
// Test fixture for EmployeeTable class.
class EmployeeTableTest : public testing::Test {
    public:
        EmployeeTable table;
};

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
```

As we can see from above, that all tests required creating an instance of `Employee` first by using the statement like `Employee new_employee` followed by adding an entry to the table `table.addEmployee(new_employee)`. Thus, we can see that our tests need some setup which is common for all and hence `Setup()` function comes to rescue for exactly such scenarios.

## 6. Setup and Teardown function in test fixture

A `Setup()` function in a test fixture is responsible for providing and executing the necessary setup instructions for our tests. Similarly, a `Teardown()` function is responsible for cleaning up operations such as deleting the memory allocated, closing the database connection etc.

To create a `Setup()` function, we just define this function in our fixture class which will [override](https://en.cppreference.com/w/cpp/language/override) the [virtual function](https://en.cppreference.com/w/cpp/language/virtual) in `testing::Test` class in GoogleTest.

For our table class, we can create the `Setup()` and `Teardown()` functions as shown below. For more details, please see [4_table_test_with_setup.cpp](https://github.com/ImperialCollegeLondon/unit_testing_Cpp_exercises/tree/main/src/Chapter3/4_table_test_with_setup.cpp).

```cpp
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
```

As we can see from above, our test looks much cleaner with the setup and teardown function. The reason for creating another test fixture for writing `Setup()` and `Teardown()` is because the first two tests do not require it.

> ## Exercise: Write a test function to check the display on screen.
>
> In some cases, we may need to check that the output or the message displayed on screen is correct. For example, we may want to check that the name of employee is displayed correctly on screen. We have a function named `displayEmployeesName` in our class `EmployeeTable` which displays the name of all employees in the table. The purpose of this exercise is to write a test function to see if it works correctly or not.
>
> We will be making use of [`std::stringstream`](https://cplusplus.com/reference/sstream/stringstream/) to capture the output of `displayEmployeesName` function. If you are interested to know why a `stringstream` class is required, you can read this article [Check my output is correct](https://stackoverflow.com/questions/40297782/c-unit-testing-check-output-is-correct).
>
> > ## Solution
> >
> > The full solution is given in [Solution](https://github.com/ImperialCollegeLondon/unit_testing_Cpp_exercises/tree/main/src/Chapter3/Exercise_solutions/a_test_display_function.cpp). We present some important parts of the solution below.
> >
> > ```cpp
> > // Check the display function work correctly.
> > TEST_F(EmployeeTableWithOneEmployee, DisplayFunctionWorksCorrectly) {
> >
> >     // STEP 1: ARRANGE
> >     std::stringstream s_input;
> >
> >     // STEP 2: ACT
> >     // You would use the following line in your application (production use) to display the employees' names on the screen.
> >     // However, this line is not necessary for the test and has been introduced only for the demonstration purpose.
> >     table.displayEmployeesName(std::cout);
> >
> >     // Pass a string stream object to the function under test instead of std::cout.
> >     // Later we will use it to compare with the expected output.
> >     table.displayEmployeesName(s_input);
> >
> >     // Store expected output in a string.
> >     std::string expected_output = "-------------------------------------------------- \n"
> >                                   "John Doe\n"
> >                                   "-------------------------------------------------- \n";
> >
> >     // STEP 3: ASSERT
> >     EXPECT_EQ(s_input.str(), expected_output);
> > }
> > ```
> >
> {: .solution}
>
{: .challenge}

## 7. Tests Filtering in GoogleTest

Sometimes, we may have some tests that take a lot of time to run. In some other case, when we are developing and testing our code, we do not want to run our entire test suite and run only one of the test that we have recently added.

GoogleTest allows us to select or omit tests using the command line option `--gtest_filter`. The general syntax to use `gtest_filter` is

```bash
$ ./your_executable --gtest_filter=Pattern[-Pattern]
```

where `Pattern` can be a valid string patterns. The `-Pattern` will run all tests except the pattern in the command. Instead of a pattern, we can also use full test name in the form `test_suite_name.test_name`.

Let us run our table tests in the file [4_table_test_with_setup.cpp](https://github.com/ImperialCollegeLondon/unit_testing_Cpp_exercises/tree/main/src/Chapter3/4_table_test_with_setup.cpp). Let us assume that the executable name is `employee_table_tests`. We get the following output.

~~~
[==========] Running 5 tests from 2 test suites.
[----------] Global test environment set-up.
[----------] 2 tests from EmployeeTableTest
[ RUN      ] EmployeeTableTest.TableIsEmptyWhenCreated
[       OK ] EmployeeTableTest.TableIsEmptyWhenCreated (0 ms)
[ RUN      ] EmployeeTableTest.TableHasSizeZeroWhenCreated
[       OK ] EmployeeTableTest.TableHasSizeZeroWhenCreated (0 ms)
[----------] 2 tests from EmployeeTableTest (0 ms total)

[----------] 3 tests from EmployeeTableWithOneEmployee
[ RUN      ] EmployeeTableWithOneEmployee.TableIsNotEmptyWhenCreatedWithOneEmployee
[       OK ] EmployeeTableWithOneEmployee.TableIsNotEmptyWhenCreatedWithOneEmployee (0 ms)
[ RUN      ] EmployeeTableWithOneEmployee.NumberOfEntriesIsOneWhenCreatedWithOneEmployee
[       OK ] EmployeeTableWithOneEmployee.NumberOfEntriesIsOneWhenCreatedWithOneEmployee (0 ms)
[ RUN      ] EmployeeTableWithOneEmployee.NumberOfEntriesIsOneLessAfterRemovingEmployee
[       OK ] EmployeeTableWithOneEmployee.NumberOfEntriesIsOneLessAfterRemovingEmployee (0 ms)
[----------] 3 tests from EmployeeTableWithOneEmployee (0 ms total)

[----------] Global test environment tear-down
[==========] 5 tests from 2 test suites ran. (0 ms total)
[  PASSED  ] 5 tests.
~~~
{: .output}

Since, we defined 5 tests, all tests run if we run the executable. Now, let us filter the tests. We want to run only the tests associated with `EmployeeTableWithOneEmployee`. We use the following command

```bash
$ ./my_test --gtest_filter=*One
```

The Output is

~~~
Employee*
Running main() from /home/lokesh/My_compiled_Libraries/test/googletest/googletest/src/gtest_main.cc
Note: Google Test filter = *OneEmployee*
[==========] Running 3 tests from 1 test suite.
[----------] Global test environment set-up.
[----------] 3 tests from EmployeeTableWithOneEmployee
[ RUN      ] EmployeeTableWithOneEmployee.TableIsNotEmptyWhenCreatedWithOneEmployee
[       OK ] EmployeeTableWithOneEmployee.TableIsNotEmptyWhenCreatedWithOneEmployee (0 ms)
[ RUN      ] EmployeeTableWithOneEmployee.NumberOfEntriesIsOneWhenCreatedWithOneEmployee
[       OK ] EmployeeTableWithOneEmployee.NumberOfEntriesIsOneWhenCreatedWithOneEmployee (0 ms)
[ RUN      ] EmployeeTableWithOneEmployee.NumberOfEntriesIsOneLessAfterRemovingEmployee
[       OK ] EmployeeTableWithOneEmployee.NumberOfEntriesIsOneLessAfterRemovingEmployee (0 ms)
[----------] 3 tests from EmployeeTableWithOneEmployee (0 ms total)

[----------] Global test environment tear-down
[==========] 3 tests from 1 test suite ran. (0 ms total)
[  PASSED  ] 3 tests.
~~~
{: .output}

Finally, let us assume that we want to run all tests except `EmployeeTableWithOneEmployee.NumberOfEntriesIsOneLessAfterRemovingEmployee`. We can use the following command

```bash
./my_test --gtest_filter=-EmployeeTableWithOneEmployee.NumberOfEntriesIsOneLessAfterRemovingEmployee
```

This will run all 4 tests except the one mentioned in the filter because of the negative sign.

### Summary

In this chapter, we learnt about the basics of test fixtures and how to use them to write tests. We also learnt the importance of `Setup()` and `Teardown()` function and saw example on how to write them. Finally, we also learnt about test filters.

{% include links.md %}

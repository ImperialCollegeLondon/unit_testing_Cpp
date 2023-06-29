---
title: "Introduction to Test Fixtures using GoogleTest"
teaching: TBC
exercises: TBC
questions:
- "What is a test fixture?"
- "How to create your own test fixture using GoogleTest?"
- "What does Setup and Teardown mean while using test fixtures?"
objectives:
- "Understand the basics of test fixture."
- "Understand how to create test fixture using GoogleTest."
- "Understand the advantages of test fixtures."
- "Understand the need of setup and teardown functions."
- "Understand how to write your own setup and teardown function."
- "Understand how to run a subset of tests."
keypoints:
- "We learnt about test fixtures in GoogleTest."
- "We learnt how to create our own test fixtures."
- "We learnt about the setup and teardown functions."
- "We learnt the advantages of test fixtures."
- "We learnt how to run a subset of tests in GoogleTest."
---
## 1. Brief Introduction of Test Fixtures
A test fixture, in the context of unit testing, refers to the preparation and configuration needed to run a set of test cases. It includes the setup of the test environment, the creation of necessary objects or resources, and the cleanup steps after the tests are executed. Test fixtures help ensure that the tests are performed in a controlled and consistent environment, providing reliable and reproducible results.

In GoogleTest, a test fixture is implemented using a test fixture class. This class serves as a container for shared setup and cleanup logic, as well as any shared objects or resources required by the test cases within the fixture.
### 1.1 When is a Test Fixture Needed?
A test fixture is typically used in the following scenarios:

1. **Shared Setup and Teardown**: When multiple test cases require a common set of setup or teardown (which means cleaning in general and is the opposite of setup) steps, a test fixture is beneficial. Instead of duplicating the setup and teardown code in each test case, we can define it once in the test fixture and reuse it across all the tests.

2. **Reducing Code Duplication**: Test fixtures help in reducing code duplication. By encapsulating the common setup and teardown logic within a fixture, we avoid duplicating the same code in multiple test cases. This improves code maintainability and reduces the chances of errors due to inconsistent or incomplete setup/teardown.

3. **Isolation and Independence**: Test fixtures provide a level of isolation and independence for each test case. Each test case within a fixture runs in its own instance of the fixture class, ensuring that changes made by one test case do not affect the others. This allows for parallel execution of test cases without interference.

Let us understand how to create a test fixture, setup and teardown functions with examples.
## 2. Problem under consideration for testing
In order to create our own test fixture, we will first explain the context or problem that we are trying to solve. We will be adding tests to check that our code works as intented by making use of test fixtures.

Consider that you want to write a program to manage the details of an employee. The program should allow you to add basic detaisl of emplyee such as 
1. Name
2. Age 
3. Basic Salary
4. Number of years of employment
5. Basic Bonus the employee has received in this year.

The program should calculate the Net Bonus, Tax and Salary based on the following rules.
1. Bonus Rule: An employee gets an additional 1000£ bonus if she or he has worked for more than 10 years.
2. Tax Rule: Tax is calculated on a combination of basic salary and net bonus as shown below.
    
    * `0` if salary is less than `10k` GBP.
    * `10%` for slar between `10K-20K` GBP.
    * `20%` for salary between `20K-50K` GBP
    * `50%` for slary greater than `50K` GBP 

Please be advised that the purpose of above rules is to create functions which can have multiple branches and hence needs additional testing. We have tried our best to keep the example simple and realistic.

Based on above, we can declare the employee class in `employee.h` as shown below ([Declaration of emloyee class](../code/Chapter3/employee.h)). 

```cpp
class Employee 
{
private:
    string name;
    float age;
    double base_salary; //salary before calculating tax and adjusting bonus.
    double number_years_employed;

    double basic_bonus; //bonus for current year.
    double net_bonus; //bonus after adjusting for experience.
    
    double tax_amount;
    double net_salary; //salary after calculating tax and adjusting bonus.

public:
    // Constructor.
    Employee(const string& employee_name, float employee_age, 
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
    string getName() const;
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

For the deifinition part, we include only a few functions here. You can find the complete definion of this class in [employee.cpp](../code/Chapter3/employee.cpp).

```cpp
// Constructor definition
Employee:: Employee(const string& employee_name, float employee_age, 
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

// Definition of function setName
void Employee::setName(const string& employee_name) 
{
    if(employee_name == "")
    {
        throw invalid_argument("Name cannot be empty");
    }
    name = employee_name;
}

// Employee gets additional £1000 bonus if they have been employed for more than 10 years.
void Employee::calcNetBonus() 
{   
    if(number_years_employed > years_exp_for_extra_bonus)
    {
        net_bonus = basic_bonus + extra_bonus;
    }
    else
    {
        net_bonus = basic_bonus;
    }
}

// Function to calculate tex amount.
void Employee::calcTaxAmount() 
{
    double salary_with_bonus = base_salary + net_bonus;
    if(salary_with_bonus <= 10000)
    {
        tax_amount = 0.0;
    }
    else if(salary_with_bonus > 10000 && salary_with_bonus <= 20000)
    {
        tax_amount = 0.1*(salary_with_bonus-10000);
    }
    else if(salary_with_bonus > 20000 && salary_with_bonus <= 50000)
    {
        tax_amount = 0.1*10000 + 0.2*(salary_with_bonus-20000);
    }
    else if(salary_with_bonus > 50000)
    {
        tax_amount = 0.1*10000 + \
                     0.2*30000 + \
                     0.5*(salary_with_bonus-50000);
    }
}

// Fucntion to calculate the ney salary.
void Employee::calcNetSalary() 
{
    net_salary = base_salary + net_bonus - tax_amount;
}
```
With this code, we now have the necessary fragments to test our `employee` class. Let us see this in action.
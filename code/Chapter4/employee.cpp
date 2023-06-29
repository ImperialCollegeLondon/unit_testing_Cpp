#include <iostream>
#include <string>
#include "employee.h"


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


void Employee::setName(const string& employee_name) 
{
    if(employee_name == "")
    {
        throw invalid_argument("Name cannot be empty");
    }
    name = employee_name;
}

void Employee::setAge(float employee_age) 
{
    age = employee_age;
}

void Employee::setBaseSalary(double employeeSalary) 
{
    base_salary = employeeSalary;
    
    //Calculate new tex based on new base salary
    calcTaxAmount();

    // Changing base salary will change net salary.
    calcNetSalary();
}

void Employee::setNumberYearsEmployed(double employeeNumberYearsEmployed) 
{
    number_years_employed = employeeNumberYearsEmployed;
    
    // Changing number of years employed will change net bonus.
    calcNetBonus();

    // Get the new tax.
    calcTaxAmount();

    // Changing net bonus will change net salary.
    calcNetSalary();
}

void Employee::SetBasicBonus(double employeeBonus) 
{
    basic_bonus = employeeBonus;

    // Changing basic bonus will change net bonus.
    calcNetBonus();

    // Get the new tax.
    calcTaxAmount();

    // Changing net bonus will affect net salary.
    calcNetSalary();
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


void Employee::calcNetSalary() 
{
    net_salary = base_salary + net_bonus - tax_amount;
}


string Employee::getName() const
{
    return name;
}


float Employee::getAge() const
{
    return age;
}


double Employee::getBasicSalary() const
{
    return base_salary;
}


double Employee::getNumberYearsEmployed() const
{
    return number_years_employed;
}


double Employee::getBasicBonus() const
{
    return basic_bonus;
}

double Employee::getNetBonus() const
{
    return net_bonus;
}


double Employee::getTaxAmount() const
{
    return tax_amount;
}

double Employee::getNetSalary() const
{
    return net_salary;
}


void Employee::displayInfo() const
{
    cout << "Name: " << name << endl;
    cout << "Age: " << age << endl;
    cout << "Base_Salary: £" << base_salary << endl;
    cout << "Number of Years Employed: " << number_years_employed << endl;
    
    cout << "Basic_Bonus: £" << basic_bonus << endl;
    cout << "Net_Bonus: £" << net_bonus << endl;
    
    cout << "Tax to be paid: £ " << tax_amount << endl;
    cout << "Net_Salary: £" << net_salary << endl;
}

// Destructor
Employee::~Employee() {
}


// int main() {
//     Employee emp("John Doe", 30, 35000.0, 12, 4000);
//     emp.displayInfo();

//     emp.setName("Jane Smith");
//     cout << "Name: " << emp.getName() << endl;

//     emp.setAge(35);
//     cout << "Age: " << emp.getAge() << endl;

//     cout << "-----------------------------------------" << endl;
//     emp.setBaseSalary(45000.0);
//     cout << "Base_Salary: £" << emp.getBasicSalary() << endl;
//     cout << "Tax to be paid: £ " << emp.getTaxAmount() << endl;
//     cout << "Net_Salary: £" << emp.getNetSalary() << endl;

//     cout << "-----------------------------------------" << endl;
//     Employee emp2("LKR", 32, 30000, 5, 2000);
//     emp2.displayInfo();

//     return 0;
// }
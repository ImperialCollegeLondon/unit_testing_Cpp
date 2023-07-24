#include <iostream>
#include <vector>
#include <string>
#include "employee_table.h"

template <class GenericEmployee>
void EmployeeTable<GenericEmployee>::addEmployee(const GenericEmployee &employee)
{
    employees.push_back(employee);
};

template <class GenericEmployee>
void EmployeeTable<GenericEmployee>::removeEmployee(const std::string &employeeName)
{
    for (auto it = employees.begin(); it != employees.end(); ++it)
    {
        if (it->getName() == employeeName)
        {
            employees.erase(it);
            break;
        }
    }
};

template <class GenericEmployee>
void EmployeeTable<GenericEmployee>::displayEmployeesName() const
{
    std::cout << "-------------------------------------------------- " << std::endl;
    for (const auto &employee : employees)
    {
        std::cout << employee.getName() << std::endl;
    }
    std::cout << "-------------------------------------------------- " << std::endl;
};

template <class GenericEmployee>
bool EmployeeTable<GenericEmployee>::isEmpty() const
{
    return employees.empty();
}

template <class GenericEmployee>
int EmployeeTable<GenericEmployee>::getEntryCount() const
{
    return employees.size();
}

template <class GenericEmployee>
void EmployeeTable<GenericEmployee>::bumpSalaryBonus(const double newBonus)
{
    for (auto employee = employees.begin(); employee != employees.end(); ++employee)
    {
        employee->setBasicBonus(newBonus);
    }
}

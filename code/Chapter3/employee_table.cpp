#include <iostream>
#include <vector>
#include <string>
#include "employee.h"
#include "employee_table.h"


void EmployeeTable::addEmployee(const Employee& employee) {
    employees.push_back(employee);
}


void EmployeeTable::removeEmployee(const std::string& employeeName) {
    for (auto it = employees.begin(); it != employees.end(); ++it) {
        if (it->getName() == employeeName) {
            employees.erase(it);
            break;
        }
    }
}

void EmployeeTable::displayEmployeesName() const {
    std::cout << "-------------------------------------------------- " << std::endl;
    for (const auto& employee : employees) {
        std::cout << employee.getName() << std::endl;
    }
    cout << "-------------------------------------------------- " << endl;
}


bool EmployeeTable::isEmpty() const {
    return employees.empty();
}


int EmployeeTable::getEntryCount() const {
    return employees.size();
}


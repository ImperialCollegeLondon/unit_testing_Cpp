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
    cout << "-------------------------------------------------- " << endl;
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


// // Main function to demonstrate the usage of the EmployeeTable class.
// int main() {
//     // Creating employee objects.
//     Employee emp1("John Doe", 30, 5000, 5, 1000);
//     Employee emp2("Jane Smith", 35, 6000, 7, 1200);
//     Employee emp3("Mike Johnson", 40, 7000, 10, 1500);

//     // Creating an instance of the EmployeeTable.
//     EmployeeTable table;

//     // Adding employees to the table.
//     table.addEmployee(emp1);
//     table.addEmployee(emp2);
//     table.addEmployee(emp3);

//     // Displaying the employees' information.
//     table.displayEmployeesName();

//     // Checking if the table is empty.
//     if (table.isEmpty()) {
//         std::cout << "The table is empty." << std::endl;
//     } else {
//         std::cout << "The table is not empty." << std::endl;
//     }

//     // Getting the number of entries in the table.
//     int entryCount = table.getEntryCount();
//     std::cout << "Number of entries in the table: " << entryCount << std::endl;

//     // Removing an employee from the table.
//     table.removeEmployee("Jane Smith");

//     // Displaying the updated employees' information.
//     table.displayEmployeesName();

//     return 0;
// }


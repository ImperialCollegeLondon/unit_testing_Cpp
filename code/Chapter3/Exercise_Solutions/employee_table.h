#ifndef employee_table_h
#define employee_table_h

#include <vector>
#include "employee.h"
#include <sstream>

class EmployeeTable {
private:
    std::vector<Employee> employees;

public:
    // Member function to add employees into the table.
    void addEmployee(const Employee& employee);

    // Member function to remove employees into the table.
    void removeEmployee(const std::string& employeeName);

    // Member function to display information (names) of all employees in the table.
    void displayEmployeesName(std::ostream& output) const;

    // Function to check if the table is empty.
    bool isEmpty() const;

    // Function to get the number of entries in the table.
    int getEntryCount() const;
};

#endif /* employee_table_h */
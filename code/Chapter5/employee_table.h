#ifndef employee_table_h
#define employee_table_h

#include <vector>

template <class GenericEmployee>
class EmployeeTable
{
private:
    std::vector<GenericEmployee> employees;

public:
    // Member function to add employees into the table.
    void addEmployee(const GenericEmployee &employee);

    // Member function to remove employees into the table.
    void removeEmployee(const std::string &employeeName);

    // Member function to display information (names) of all employees in the table.
    void displayEmployeesName() const;

    // Function to check if the table is empty.
    bool isEmpty() const;

    // Function to get the number of entries in the table.
    int getEntryCount() const;

    // Member function to change the bonus to all employees.
    void bumpSalaryBonus(const double newBonus);
};

#endif /* employee_table_h */

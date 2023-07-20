#ifndef employee_table_h
#define employee_table_h

#include <vector>

template <class GenericEmployee>
class EmployeeTable
{
private:
    // See the note number 2 given in exercise_with_mocks on why we are using pointers here.
    std::vector<GenericEmployee*> employees;

public:
    // Member function to add employees into the table.
    void addEmployee(GenericEmployee* employee)
    {
        employees.push_back(employee);
    }

    // Other functions may or may not require changes.
    // For brevity, we are using only two functions.

    // Member function to change the bonus to all employees.
    void bumpSalaryBonus(const double newBonus)
    {
        for (auto& employee : employees)
        {
            employee->setIncreasedBasicBonus(newBonus);
        }
    }
};

#endif /* employee_table_h */

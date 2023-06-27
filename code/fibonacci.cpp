#include <iostream>

/*Returns the n'th term of the Fibonacci sequence.*/
int recursive_fibonacci(int n)
{
    if (n <= 1) {
        return n;
    } else {
        return recursive_fibonacci(n - 1) + recursive_fibonacci(n - 2);
    }
}

int main()
{
    std::cout << recursive_fibonacci(0) << "\n";
    std::cout << recursive_fibonacci(1) << "\n";
    std::cout << recursive_fibonacci(2) << "\n";
    std::cout << recursive_fibonacci(3) << "\n";
    std::cout << recursive_fibonacci(4) << "\n";
    std::cout << recursive_fibonacci(5) << "\n";
    std::cout << recursive_fibonacci(6) << "\n";
    return 0;
}

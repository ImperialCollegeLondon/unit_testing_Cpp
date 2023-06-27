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
    // Manual tests
    // Case 1: When n is 0 or 1
    int n = 0;
    std::cout << "Fib(" << n << ") = " << recursive_fibonacci(n) << "\n";

    n = 1;
    std::cout << "Fib(" << n << ") = " << recursive_fibonacci(n) << "\n";

    // Case 2: When n is greater than 1.
    n = 5;
    std::cout << "Fib(" << n << ") = " << recursive_fibonacci(n) << "\n";

    // Case 3: When n is negative.
    n = -3;
    std::cout << "Fib(" << n << ") = " << recursive_fibonacci(n) << "\n";

    return 0;
}

#include <iostream>
#include <cmath>

// Class to calculate Fibonacci numbers
class Fibonacci {
public:
    int getNthFibonacci(int n) {
        if (n <= 1) return n;
        int a = 0, b = 1, c;
        for (int i = 2; i <= n; i++) {
            c = a + b;
            a = b;
            b = c;
        }
        return b;
    }
};


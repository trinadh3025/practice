#include <iostream>
#include <cmath>

// Class to check Armstrong numbers
class Armstrong {
public:
    bool isArmstrong(int num) {
        int original = num;
        int sum = 0;
        int digits = log10(num) + 1;
        while (num > 0) {
            int digit = num % 10;
            sum += pow(digit, digits);
            num /= 10;
        }
        return sum == original;
    }
};



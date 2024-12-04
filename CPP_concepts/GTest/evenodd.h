#include <iostream>
#include <cmath>


// Class to determine if a number is even or odd
class EvenOdd {
public:
    bool isEven(int num) {
        return num % 2 == 0;
    }

    bool isOdd(int num) {
        return num % 2 != 0;
    }
};



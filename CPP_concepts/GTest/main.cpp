#include "fibonacci.h"
#include "evenodd.h"
#include "armstrong.h"

using namespace std;

// Main for functional demonstration (Optional, can be removed for testing purposes)
int main() {
    Fibonacci fib;
    EvenOdd eo;
    Armstrong arm;

    cout << "5th Fibonacci: " << fib.getNthFibonacci(5) << endl;
    cout << "Is 10 Even? " << (eo.isEven(10) ? "Yes" : "No") << endl;
    cout << "Is 153 Armstrong? " << (arm.isArmstrong(153) ? "Yes" : "No") << endl;

    return 0;
}


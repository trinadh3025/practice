#include <iostream>
#include <string>
#include <typeinfo>

class Base {
public:
    virtual void display() { std::cout << "Base class\n"; }
    virtual ~Base() = default; // Virtual destructor
};

class Derived : public Base {
public:
    void display() override { std::cout << "Derived class\n"; }
};

void demonstrateCasting() {
    std::cout << "1. Static Cast:\n";
    {
        int a = 42;
        double b = static_cast<double>(a); // Explicit conversion
        std::cout << "int to double: " << b << "\n";

        Derived derivedObj;
        Base* basePtr = static_cast<Base*>(&derivedObj); // Upcasting
        basePtr->display();
    }

    std::cout << "\n2. Dynamic Cast:\n";
    {
        Base* basePtr = new Derived();
        Derived* derivedPtr = dynamic_cast<Derived*>(basePtr); // Downcasting
        if (derivedPtr) {
            derivedPtr->display();
        } else {
            std::cout << "Dynamic cast failed\n";
        }

        delete basePtr;

        Base baseObj;
        Base* invalidBasePtr = &baseObj;
        Derived* invalidDerivedPtr = dynamic_cast<Derived*>(invalidBasePtr);
        if (!invalidDerivedPtr) {
            std::cout << "Dynamic cast failed for invalid base pointer\n";
        }
    }

    std::cout << "\n3. Const Cast:\n";
    {
        const int num = 10;
        int* modifiablePtr = const_cast<int*>(&num); // Removes const
        *modifiablePtr = 20; // Undefined behavior if the original object is truly const
        std::cout << "Const cast result: " << *modifiablePtr << "\n";
    }

    std::cout << "\n4. Reinterpret Cast:\n";
    {
        int a = 42;
        void* voidPtr = &a;                           // Implicit void* conversion
        int* intPtr = reinterpret_cast<int*>(voidPtr); // Back to int*
        std::cout << "Reinterpreted value: " << *intPtr << "\n";
    }

    std::cout << "\n5. Preventing Implicit Conversions:\n";
    {
        class NonConvertible {
        public:
            explicit NonConvertible(int value) : val(value) {}
            int getValue() const { return val; }

        private:
            int val;
        };

        NonConvertible obj1(42); // Allowed due to 'explicit'
        // NonConvertible obj2 = 42; // Error: Prevented by 'explicit'
        std::cout << "Non-convertible value: " << obj1.getValue() << "\n";
    }

    std::cout << "\n6. Avoiding Implicit Conversions with C++ Casts:\n";
    {
        class A {
        public:
            A() = default;
            A(const A&) = delete; // Prevent copy construction
            explicit A(int) {}    // Prevent implicit conversions
        };

        A obj1;         // Default construction
        A obj2(42);     // Allowed due to 'explicit' constructor
        // A obj3 = 42; // Error: Explicit prevents implicit conversion
    }
}

int main() {
    demonstrateCasting();
    return 0;
}


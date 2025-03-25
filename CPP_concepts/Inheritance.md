Output:
trinadh@Trinadh:~/practice/CPP_concepts$ ./a.out
Base constructor
Base constructor
Derived1 constructor
Base constructor
Derived2 constructor
Base constructor
Derived1 constructor
Derived2 constructor
MultiDerived constructor
Base show: 2, BBB:8|�p�U
Derived1 show: 0, , 3
Derived2 show: 0, , 4
MultiDerived show: 0, , 0, 0, 1
MultiDerived destructor
Derived2 destructor
Derived1 destructor
Base Destructor
Derived2 destructor
Base Destructor
Derived1 destructor
Base Destructor
Base Destructor

Memory Layout Summary (Approximation):
Base Class (Base):

+---------------------+
| baseData1 (4 bytes)  |
| baseData2 (3 bytes)  |
+---------------------+
Total size: 7 bytes (with padding, usually 8 bytes).

Derived1 Class (inherits from Base):
+-----------------------+
| baseData1 (4 bytes)    |
| baseData2 (3 bytes)    |
| derivedData1 (4 bytes) |
+-----------------------+
Total size: 12 bytes (due to padding for derivedData1).

Derived2 Class (inherits from Base):
+-----------------------+
| baseData1 (4 bytes)    |
| baseData2 (3 bytes)    |
| derivedData2 (8 bytes) |
+-----------------------+
Total size: 16 bytes (due to padding for derivedData2).

MultiDerived Class (inherits from Derived1 and Derived2):
+-----------------------+
| baseData1 (4 bytes)    |
| baseData2 (3 bytes)    |
| derivedData1 (4 bytes) |
| padding (1 byte)       |
| derivedData2 (8 bytes) |
| padding (2 bytes)      |
| multiDerivedData (1 byte)|
| padding (7 bytes)      |
+-----------------------+
Total size: 32 bytes (with padding to ensure proper alignment).

Virtual Table (vtable) Consideration:
Virtual Inheritance: If Base had virtual functions (like show()), each object of a derived class would have a hidden pointer to the virtual function table (vtable). The pointer to the vtable typically adds 4 to 8 bytes to the size of the object.

Each class that has virtual functions will have its own vtable (unless it inherits virtual functions from a base class).

Memory Layout with vtables:
Base Class (Base):
+------------------------+
| vptr (8 bytes)         |  (Pointer to vtable)
| baseData1 (4 bytes)     |
| baseData2 (3 bytes)     |
+------------------------+

Derived1 Class:
+------------------------+
| vptr (8 bytes)         |
| baseData1 (4 bytes)     |
| baseData2 (3 bytes)     |
| derivedData1 (4 bytes)  |
+------------------------+

Derived2 Class:
+------------------------+
| vptr (8 bytes)         |
| baseData1 (4 bytes)     |
| baseData2 (3 bytes)     |
| derivedData2 (8 bytes)  |
+------------------------+

MultiDerived Class:
+------------------------+
| vptr (8 bytes)         |
| baseData1 (4 bytes)     |
| baseData2 (3 bytes)     |
| derivedData1 (4 bytes)  |
| padding (1 byte)        |
| derivedData2 (8 bytes)  |
| padding (2 bytes)       |
| multiDerivedData (1 byte)|
| padding (7 bytes)       |
+------------------------+

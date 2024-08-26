# General Course Notes

## Exam Reflection

This exam is definitely more difficult and tests the topics taught in the course to a much further extent than the CS 124 exam does. For instance, move semantics are one of the last topics taught in this course and they appeared on my exam. Knowing make is not as important for this course's exam as I thought it would be, I just manually compiled with the terminal. Do not practice learning how to use and set up the vscode debugger beforehand because vscode extensions, the C++ extension are disabled in the test instance of prairelearn and the debugging profiles can't be created. Tne bulk of my time on the exam was spent doing one big programming problem with many steps to it, in my case it was implement the rule of 5 (destructor, copy constructor, copy assignment operator, move constructor, and move assignment operator) as well as default constructor and a few other methods for a circular linked list. if your code times out you will get a zero for the entire problem. One specific thing I never remember being mentioned in the course but came up on the exam was that object files can be compiled as well, and you pass them into the compiler just like you would pass in source files.

## General Notes

- Declaration of a function is what goes in the header, definition of a function is what goes in the actual implementation cpp file
- To add a folder for clang/gcc for header files and make it as if the header files in that folder are in the root directory you would do

```bash
clang++ -I [folder_name]
```

- If you have a folder called test and you do -Itest and a header inside that folder called tim you can then do ``#include "tim"``

## Make

- Review make notes in my cs notes [here](../..CS Notes/CMake.md)

## Reading from stdin

```cpp
#include <iostream>
using std::cin;
// cin works by white space any kind seperator and can read it into a string or into or whatever
string name;
int age;
cin >> name >> age;
// to read an entire line
using std::getline;
string line;
getline(cin, line);
```

## File I/O

```cpp
#include <fstream>
using std::ofstream;
// normal file write that overrides everything in file
ofstream ofs {"filename.txt"};
// append file write that adds on to what already is in the file
ofstream ofs {"filename.txt", ofstream::app};
if (!ofs.is_open()) {
 // check if file wasn't open in
}
// just like any other streams
ofs << "string";

using std::ifstream;
ifstream ifs {"filename.txt"};
// same is open checks as out file work
int a;
ifs >> a;

```

- You can call `fail()` on any `istream` object and it will tell you if the stream has failed to read data into a specific type

- `clear()` resets the flags `good`, `bad`, and `fail` to their default values (true, false, and false, respectively) on an istream
  - this doesn't move the head/extraction arm and it will still be on the invalid character
- `ignore(num_characters, type_character)` will ignore characters until it has either ignored the number of characters specified in the first argument, or has hit a type character, like whitespace or newline, which ever comes first

## Link Errors

- Definition error is when linker has a function declared in a header but cannot find a definition of it implemented in a cpp file, this appears as the following error: `undefined reference to function_name(int x, int y)`

## C++ Exceptions

- Way to raise errors without the option of ignoring them because if you don't catch and handle them your program will stop
- To throw a basic exception

```cpp
#include <stdexcept>
throw std::runtime_error("Error message");
```

- Runtime error is equivalent to something like `new Exception("error message")` in java
**Catching Exceptions to Avoid Program Halt**

```cpp
try {
// lines of code that can throw an std::runtime_error
}
// this is the syntax its a const reference that you don't change to the error thrown
catch(const std::runtime_error &e) {
// handling for the error here
}
// catch block that will catch any kind of exception type
catch(...) {
// code goes here for universal catch handler
}
```

- If you have multiple catch blocks you order them top down and the first catch block with matching exception type and no other catch block will be called
  - Matching means it can be the same type of a parent type works too for a child exception, for instance logic_error type will work to catch a invalid_argument which is a child of logic_error
- In a catch block you can just use the `throw;` keyword on its own to rethrow the same exception you are catching in the event that the handler can't fully handle everything and the error needs to be brought back up
**Precondition**: Something that has to be true before your code executes (length and width should be both positive before calculating the area)
**Postcondition**: Something that has to be true after your code executes (the area of the rectangle is correctly calculated

## Assert Statements

```cpp
// from the c language
#include <cassert>
int condition = 0;
assert(condition);
```

- Asserts are mainly used to check for programming errors and to debug and not to handle and process runtime errors like exceptions are
- If assert evaluates to false, it will stop your program execution like an uncaught exception would and indicate where the assert failed to evaluate
- Asserts cannot be caught like exceptions can

## Formal Testing

**Unit Tests**: Meant to test the system at its lowest level programmer to programmer, make sure that output of program/function/block matches the expected output

- Acronym FIRST
  - fast: you run them often so you want them to run fast
  - independent: one unit test should not depend on another test
  - repeatable: you can run the tests over and over again
  - self-checking: test can verify on its own if its passed or not
  - timely: write the unit test when we write the code so you can catch errors with that part of the code you right if it changes later
**Component Tests**: one level above unit tests, test to make sure that one component of the system works
**Integration Tests**: One level above component tests, test to make sure that multiple components of the system work together correctly
**Coverage Levels/Measurement**: Different levels used to determine to what extent your tests are covering your codebase, higher level is more coverage but harder/impractical to implement
- S0: Every method called
- S1: Every method from every call site
- C0: Every statement
- C1: Every branch in different directions
- C2: Every path

## Pointers/References

- Good practice is to put the character on the type and not on the variable or method name

- Declarative case: `int& a` or `int* p`
  - `&`: reference indicator
  - `*`: pointer indicator
- in a variable: `x = &a`  or `*p = 5`
  - `&`: the memory address of the variable
  - `*`: pointer indicator
**const references**: `const int& ii`: acts as a read only variable and prevents you from using ii to reassign whatever value ii is referencing through using ii, you would not be able to call `ii = ...`
- typically you cannot have a reference pointed to a literal (`int& a = 11` would be improper syntax) but you can have const references pointing to literals

## User Defined Types

- Types with specific behaviors and organization of data in them, different components of our program like a vector, matrix, input streams, idea behind interfaces and acts as blueprint for classes and then objects
**Interface**: System that may abstract super specific implementation details while allowing a specific way it user to interact with it and understand its functionality and expected inputs and outputs

## C++ Classes

- The class definition goes in the header and then the implementation of the methods can go in the cpp file with `CLASSNAME::METHOD_NAME(){}` just like in Mod lab

- for accessor methods and getters, you want to use const keyword for instance `int getAge() const` so that const references can call this method and to prevent any properties of the object this method lives in from being modified by it
  - It's just a getter, it shouldn't be modifying anything
  - In C++, if you have a const reference to an object you can only call const methods inside that object
**Initializer List**: Standard practice of writing constructors in C++ now
- Use curly braces for the initialization to prevent narrowing from occurring
- You can do assignment of variables in classes just like you can in java to initialize them in combination with initializer list, so you don't have to include them in initializer list

```cpp
// the new way
class Triangle {
 private:
  int base;
  int height;
 public:
  Triangle() : base{0}, height{0} {}
  Triangle(int newBase, int newHeight) : base{newBase}, height{newHeight} {
   if (base < 0 || height < 0) {
    throw runtime_error("Triangle base or height cannot be less than zero.");
   }
  }
};
```

## Operator Overloading

- Allows you to define behaviors of operators on two different types
**Member Implementation**: function declaration for member of class, class type would be left of operator and the single argument passed as const reference would be right of operator:

```cpp
// < can be replaced with any operator in cpp
ReturnType operator<(const Type& rightOfOperator);
```

**Nonmember Implementation**: Can also do left, right syntax for non class member operator overload functions for binary operators (operators with 2 sides like `==` and `>`), common example is toString java equivalent in C++ for operator overloading:

```cpp
ostream& operator<<(ostream& leftCoutStream, Type& rightOfOperator);
```

**Copy Assignment**: Overloading the = Operator

- Compiler's default implementation is that it takes all the properties from right and sets the left values to them
- Always return a self reference, so you do `Type& operator=`
- In copy assignment method body you can access private variables of your own and the other object
**Prefix/Postfix Operator Overloading Note**: Prefix has nothing attached to it, just `ReturnType& operator--();` for member class but `ReturnType& operator--(int)` for postfix

## Number Storage on Computers Review

**Two's Complement**: Method to store negative numbers, use additive inverses `$3 + -3 = 0$` in binary, `$0011 + 1101 = 10000$`, 1 leftmost from result gets dropped to be 0 `$-> 1101$` is the representation of -3 in two's complement

- To compute two's complement easily: take positive number, flip all the bits and add 1
**Floating Point Number Store**: Comprised of sign (positive or negative), Exponent, and Mantissa
Start by putting it in base 2 scientific notation: `$3.5 = 1.75 xx 2^1$`
- **Sign**: Negative is 1, positive is 0, here it is 0
- **Mantissa**: 0.75 (it is implied from scientific notation that there will be a 1. before the 0.75)
  - Stored in binary as integer value I, `$I / (2^("mantissa bit size")) = "mantissa"$`
- Exponent: **1**
- Bias Function: for exponent calculation simplification/more efficient storage
  - `$"bias"(n) = 2^(n-1) - 1$`
- Formula for putting it together: `$(-1)^"sign" xx 2^(e - "bias") xx (1 + "mantissa")$`

## Heap Allocated Objects

If you want to delete an object, you do `delete object_ptr;`
If you want to delete an array, you do:

```cpp
int* array = new int[50];
delete[] array;
```

To create and initialize primitives on the heap, do:

```cpp
int* prim_int_ptr = new int{5};
```

To create a 2D Array:

```cpp
int numRows = 7;
int numCols = 5;
int** arr = new int*[numRows];
for (int _ = 0; _ < numRows; ++_) {
 arr[_] = new int[numCols];
}
```

## Debugging Tools

- Command arguments you add to clang++ which gives you a report and adds some telemetry to your binary which gives you more useful errors for debugging purposes

- -g is the general debugging flag you can put into compilers and they will add more info to the binary
**AddressSanitizer (ASan)**: Checks for memory leaks and sanitizes addresses
**Undefined Behavior Sanitizer (UBSan)**: Checks for undefined behavior, index errors, etc.
**Valgrind**: Toolchain that provides more compiler flags for memory checking and memory leaks

## Resource Acquisiction and Initialization (RAII)

- Idea behind RAII is to represent resources that open and close or alloctte and deallocate things and put them into one class that handles it all and takes care of it for you so you can just interact with it without having to worry about memory leaks

- Destructors of objects get implicitely called if the object was created on the stack as a value inside of a scope and that scope was exited

## Copy Semantics

- Default C++ compiler copy (`Object& operator=(Object& other);` overload or `Object(const Object& other)` is just to copy each member/property over by value, pointer address 1 goes to pointer address other
  - This wouldn't make an array duplicate just copy the pointer from the first array object pointer to the second object
  - This is an instance of a shallow copy

- Deep copy would be manually overloading the assignment operator yourself, making a copy of the array and then setting the pointer of the array of the new object to the copy you just made
  - Depends on what you want for your use case
**Rule of Zero and Rule of Three**: Default destructor, copy assignment operator, copy constructor, either you implement all three or you implement none
- For default constructor just set the default values that you want where they are declared

```cpp
class Object {
 public:
  // Copy assignment operator overload
  Object& operator=(Object& other);
  // Copy constructor
  Object(const Object& other);
  // Default constructor
  Object();
}
```

## Templates

**Function Templates**: Allow generic behavior to be put inside function and called for different types

- For instance min and max implementations don't matter based on the type as long as the objects are comparable

```cpp
template <typename Type> Type& min(Type& a, Type& b) {
 if (a < b) {
  return a;
 }
 return b;
}
```

**Class Templates**: The same thing as functional templates, allow for functionality like `List<Type>` exactly like in java with generics

```cpp
template <typename Type> class Stack {
 private:
  vector<Type> list;
}
```

## Inheritance/Polymorphism Review

In cpp to extend you do:

```cpp
// Base class
class A {

}

class B: modifier A {

}
```

- There are modifiers to visiblity of inheritance
**Public extend**: Is a concept, standard java inheritance extends keyword
**Protected extend**: You cannot cast A to B if its protected, and everything that is public in A becomes protected in B
**Private extend**: Implements an in terms off relationship, you can use base classes public methods but users of class B would not be able to use public methods or values of class A

- useful if you want to make your own extension of the vector standard library class and control how people interact with it
if you have `A object = B;`, if you want to have B override a method of A like it does in Java instead of doing `@Override` you use the `virtual` keyword for method A
**Pure virtual functions**: Equivalent of abstract functions in java that someone needs to extend to implement, used as:
- `virtual string function() = 0;`
**Virtual Destructors**: Allow you to delegate deletion to each type that inherits from the base, this is generally a good idea to do

## Trees Review

- Depth of trees are zero indexed: root is depth 0, 1 down is 1, etc.

- Binary search tree rules: to the left value_left < value_root, to the right value_right >= value_root
- You want to do a postorder traversal for destructors and clearing up trees to avoid deleting something before you've deleted its children and creating a memory leak
- Recurse all the way left to find the smallest element in the tree, all the way right for the largest element in the tree

## Graphs Reviews

Different ways to store graphs: Adjacency matrix, vertices and what those vertices are connected to (adjacency list), or two lists, one of vertices and one of pairs, each pair being two references to two vertices marking an edge between vertices (this third method is how they will be stored in CS 128)
**Simple graph**: Two edges cannot connect the same two vertices
**Multigraph**: Two or more edges can connect the same two vertices
**Connected graph**: graph where every vertex can be reached from another vertex, they are all connected together
**Acyclic Graph**: graph with no cycles, you can't return to a node you were at before without using the existing paths you've already used

- Trees are examples of acyclic graphs

## Design Patterns

**Strategy Pattern**: You have an interface, a strategy with how to interact with that interface, and then implementations of that strategy of how you interact with that interface
Example: Ducks can quack and ducks have a type of quack behavior that they can store (interface), then there is a quack behavior object (strategy) that is the parent for all of the different ways in which a duck can quack

## Iterators

**Container**: Storage that holds objects we have, has a start and end in the context of iterators, example: `vector`, `list`, etc. in C++
**Iterator**: Let's you move through the items of the container without having to know how they are laid out, there is a next item, functionality that you should be able to access from the start all the way to the end example: `list.begin()`, `list.end()`, etc.

- Abstraction of a pointer to some element in a container that is part of a sequence going from start to finish in that container
- You don't need to see the pointer itself, but the data contained inside a node for example is what is important to you
**Iterators must have**:
- dereferencing data at current iterator **(operator*)**
- going to the next data **(operator++)**
- checking if other iterator is at the same spot (`operator==`)
**Functions**:
find: takes, start, end, and value to look for and returns the iterator of where it finds the value, that iterator can then be dereferenced
Extend this class to implement iterator: `public iterator<forward_iterator_tag, Type>`

## Move Semantics

- Two more things to add to rule of three (destructor, copy constructor, assignment operator overload) are move constructor, and move assignment operator
**Move constructor**: `Type(Type<T>&& other);`

- for move constructors, you want to copy the data over from the other to yours shallow copy and clear up the stuff and release it from other
**Move assignment operator** `Type& operator=(Type<T>&& other);`
- for move assignment operator the object already has its own stuff so free up its own stuff first and then shallow copy everything over from other into it and clear up other
Point of moving is to reduce copying and make it faster
`Type&&`: Dual meaning, rvalue reference and universal reference
**lvalue**: something that occupies memory and lives beyond an expression, like a variable
**rvalue**: everything else that isn't an lvalue (literals, things being passed into lvalues from the right, temporary objects)
Function `move()`: casts something to an rvalue

## Smart Pointers

- classes that have data members that are raw pointers and are wrappers for pointers
`unique_ptr<T>`: exclusively own the raw pointer and manage it

- Copy semantics are disabled for this so you can't copy this by value anywhere
- `make_unique<T>(T item)`: used to initialize unique pointer instead of using new keyword
`shared_ptr<T>`: shared ownership, there is a reference counter that keeps track of all the times shared pointer is copied and increments it and decrements it when the shared pointers are destroyed, when the last shared pointer is destroyed, it will also free up the raw pointer it is designed to keep track of
- `make_shared<T>(T item)`: used to initialized shared pointer objects instead of directly the new keyword like we would for raw pointers
- if you want to implement your own shared pointer, make a pointer to reference count on the heap somewhere and then have all instances of your shared pointers for this specific pointer work on it and modify it
`weak_ptr<T>`

#include <iostream>

template <typename... T>  // Template parameter pack
void printArgs(T&&... args) {  // Function parameter pack
    // Fold expression to print each argument
    ((std::cout << args << " "), ...);  
    std::cout << "\n";
}

int main() {
    int x = 10;
    double y = 20.5;
    std::string z = "Hello";

    // First instantiation with (x, y)
    printArgs(x, y);  // T... becomes <int&, double&>
    
    // Second instantiation with (x, z)
    printArgs(x, z);  // T... becomes <int&, std::string&>
}

// soduko.hpp

#ifndef SODUKO_HPP
#define SODUKO_HPP

class Calculator {
public:
    // Constructor
    Calculator();

    // Basic arithmetic operations
    int add(int a, int b);
    int subtract(int a, int b);
    int multiply(int a, int b);
    float divide(float a, float b);

private:
    // Private helper function
    float checkDivisor(float divisor);
};

#endif // SODUKO_HPP

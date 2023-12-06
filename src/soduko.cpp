// calculator.cpp

#include "soduko.hpp"

// Constructor
Calculator::Calculator() {
    // Constructor implementation (if needed)
}

// Addition
int Calculator::add(int a, int b) {
    return a + b;
}

// Subtraction
int Calculator::subtract(int a, int b) {
    return a - b;
}

// Multiplication
int Calculator::multiply(int a, int b) {
    return a * b;
}

// Division
float Calculator::divide(float a, float b) {
    // Check for division by zero
    if (b == 0) {
        // Handle the error (for simplicity, returning 0 here)
        return 0;
    }

    // Use the private helper function to check divisor
    float validDivisor = checkDivisor(b);

    // Perform the division
    return a / validDivisor;
}

// Private helper function to check divisor
float Calculator::checkDivisor(float divisor) {
    // Additional checks or modifications can be added here
    return divisor;
}

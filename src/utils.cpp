#include <iostream>
#include <sstream>
#include <string>
#include <cstring>

#include "./sudoku.hpp"

const constexpr char INVALID_RANGE[36] = "Invalid integer. Not within [0..9].";
const constexpr char UNSAFE_NUMBER[48] = "Given integer cannot be placed in that position";

bool strings_equal(const char* str,char const *cond) {
    return strcmp(str,cond) == 0;
}

/// @brief Asks user to enter the coordinates of the grid to update
std::pair<int,int> parseCoordinates() {
    std::cout << "\nEnter grid coordinates (row,column): " << std::endl;

    std::string input;

    // Read the entire line of input
    std::getline(std::cin, input);

    std::stringstream ss(input);
    char comma;
    int row, column;

    if (ss >> row >> comma && comma == ',' && ss >> column && ss.eof()) {
        if (SudokoGrid::isNumberInRange(row) && SudokoGrid::isNumberInRange(column)) return std::make_pair(row, column);
        std::cout << INVALID_RANGE << std::endl;
    } else std::cout << "Invalid input. Expected a comma-separated pair of numbers." << std::endl;

    // If there's an error, recursively call the function to prompt again
    return parseCoordinates();
}    

bool alertUserForInvalidNumber(const SudokoGrid& grid,const int i,const int j,const int number) {
    if (grid.isNumberInRange(number)) {
        if (grid.isSafe(i,j,number)) return true;
        std::cout << UNSAFE_NUMBER;
    }
    else std::cout << INVALID_RANGE;

    std::cout << std::endl;

    return false;
}

int parseIsSafe(SudokoGrid& grid,std::pair<int,int>& cords) {
    std::cout << "Enter new replacement number : " << std::endl;

    int number;

    while (!(std::cin >> number)) {
        // If extraction fails, clear the error state and ignore the invalid input
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        std::cout << "Invalid input. Please enter a valid number." << std::endl;

        return parseIsSafe(grid,cords);
    }

    auto [i,j] = cords;
    if (alertUserForInvalidNumber(grid,i,j,number)) return number;

    return parseIsSafe(grid,cords);
}

/// @brief Starts interactive mode 
void startInteractiveMode(SudokoGrid grid) {
    int missingNumbers = grid.countMissingBoxes();
    while(missingNumbers != 0) {
        std::cout << grid << std::endl;

        std::pair<int,int> cords = parseCoordinates();
        int number = parseIsSafe(grid,cords);

        missingNumbers++;
        grid.update(cords.first,cords.second,number);
    }        

    std::cout << "Congrats, you solve the puzzle!" << std::endl;
}

namespace {
    /// @brief Request row
    /// @return Returns row number
    int requestRowFromUser(SudokoGrid& grid,const int row) {
        std::string rowInput;
        std::cout << "Row " << row + 1 << ": ";
        std::getline(std::cin, rowInput);

        // Validate the length of the input row
        if (rowInput.length() != SudokoGrid::SIZE) {
            std::cout << "Invalid row length. Please enter " << SudokoGrid::SIZE << " digits." << std::endl;
            return row;
        }

        for (int j = 0; j < SudokoGrid::SIZE;j++) {
            int value = rowInput[j] - '0';
            
            if (!alertUserForInvalidNumber(grid,row,j,value)) return row;

            grid.update(row,j,value);
        }

        return row + 1;
    }
}

/// @brief Asks user to enter grid
SudokoGrid requestGridFromUser() {    
    std::cout << "Enter the Sudoku grid row by row:" << std::endl;

    SudokoGrid grid = SudokoGrid();
    int row = 0;

    while (row < SudokoGrid::SIZE) {
        row = requestRowFromUser(grid,row);
    }

    return grid;
}

/// @brief Asks user for file name
SudokoGrid requestGridFromFile() {    
    std::cout << "Enter file directory : ";
    
    std::string input;
    std::getline(std::cin,input);

    const std::string EXTENSION = ".sudoko";

    bool isValid =  input.length() >= EXTENSION.length() &&
           input.substr(input.length() - EXTENSION.length()) == EXTENSION;

    if (!isValid) {
        std::cout << "Invalid file is given (files have to end with .sudoko)" << std::endl;
        exit(1);
    }

    SudokoGrid grid = SudokoGrid::fromFile(input.c_str());

    return grid;
}
// sudoko.hpp

#ifndef SUDOKO_HPP
#define SUDOKO_HPP

#include <iostream>
#include <cmath>
#include <cassert> 
#include <fstream>
#include <tuple>
#include <array>
class SudokoGrid {
    public : static constexpr int SIZE = 9;
    private :
        static constexpr int SUBMARTIX_SIZE = 3;
        
        int matrix[SIZE][SIZE] = {0};

        /// @brief Inner method to avoid static linking errors 
        void __random(const int missingNumbers) noexcept;

        /// @brief Inner method to avoid static linking errors 
        void __fromFile(const char* fileName);

        /// @brief Inner method for solve
        bool __solve(
            std::array<int, SudokoGrid::SIZE> row,
            std::array<int, SudokoGrid::SIZE> col,
            std::array<int, SudokoGrid::SIZE> box,
            int i,
            int j
        ) noexcept;

        /// @brief Applies bitmasks to grid
        std::tuple<
            std::array<int, SIZE>,
            std::array<int, SIZE>,
            std::array<int, SIZE>
        > applyBitmasks() noexcept;

        /// @brief Generates random number
        int randomNumber(const int n) const noexcept;

        /// @brief Fill 3 x 3 martixes
        void fillSubmartix(int const row,int const col) noexcept;    

        /// @brief Checks whether number can be put in 3 x 3 martix
        bool possibleToPlaceInSubmartix(int rowStart, int colStart, int num) const noexcept;
        
        /// @brief Recursively fill remaining matrix
        bool fillRemainingMartix(int i,int j) noexcept;

        /// @brief Check in the row for existence
        bool existenceOfRow(int i, int num) const noexcept;

        /// @brief Check in the column for existence
        bool existenceOfColumn(int j, int num) const noexcept;

        /// @brief Removes `missingNumbers` number of digits from grid
        void removeDigits(const int missingNumbers) noexcept;

        /// @brief Finds the submartix index of an element at position [i][j] in the grid
        int getBox(int i, int j) { return i / 3 * 3 + j / 3; }
    public : 
        /// @brief Fills hhole grid with 0 
        SudokoGrid() {}
    
        /// @brief Randomly genereates grid
        static SudokoGrid random(const int missingNumbers = 20) noexcept {
            SudokoGrid sudoko = SudokoGrid();
            sudoko.__random(missingNumbers);
            return sudoko;
        }

        /// @brief Creates grid from a file
        static SudokoGrid fromFile(const char* fileName) { 
            SudokoGrid sudoko = SudokoGrid();
            sudoko.__fromFile(fileName);
            return sudoko;
        }

        /// @brief Checks whether number is between 0 and 9
        static bool isNumberInRange(const int number) {
            return number >= 0 && number <= SudokoGrid::SIZE;
        }

        /// @brief Converts to string
        friend std::ostream& operator<<(std::ostream& os, const SudokoGrid& sudoku);

        /// @brief Check if safe to put in cell
        bool isSafe(int i,int j,int num) const noexcept;

        /// @brief Updates 'index' in matrix with number 
        void update(int i,int j,int num) noexcept;

        /// @brief Counts the number of missing boxes in the Sudoku grid
        int countMissingBoxes() const noexcept;

        /// @brief Solves the grid
        /// @return Whether solution exists
        bool solve() noexcept;
};

#endif // SUDOKO_HPP

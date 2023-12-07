// sudoko.hpp

#ifndef SUDOKO_HPP
#define SUDOKO_HPP

#include <iostream>
#include <cstdint>
#include <cmath>

class SudokoGrid {
    private :
        static constexpr uint8_t SIZE = 9;
        static constexpr uint8_t SUBMARTIX_SIZE = 3;
        
        uint8_t matrix[SIZE][SIZE] = {0};

        /// @brief Inner random method to avoid static linking errors 
        void __random() noexcept;

        /// @brief Fill 3 x 3 martixes
        void fillSubmartix(uint8_t const row,uint8_t const col ) noexcept;    

        /// @brief Checks whether number can be put in 3 x 3 martix
        bool possibleToPlaceInSubmartix(uint8_t rowStart, uint8_t colStart, uint8_t num) const noexcept;
        
        /// @brief Recursively fill remaining matrix
        void fillRemainingMartix() noexcept;
    public : 
        /// @brief Fills hhole grid with 0 
        SudokoGrid() {}
    
        /// @brief Randomly genereates grid
        static SudokoGrid random() noexcept {
            SudokoGrid sudoko = SudokoGrid();
            sudoko.__random();
            return sudoko;
        }

        /// @brief Converts to string
        friend std::ostream& operator<<(std::ostream& os, const SudokoGrid& sudoku);
};

#endif // SUDOKO_HPP

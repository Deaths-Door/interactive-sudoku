// soduko.cpp

#include "sudoku.hpp"

std::ostream &operator<<(std::ostream& os,const SudokoGrid& sudoku) {
    for (auto i = 0; i < sudoku.SIZE; i++) {
        for (auto j = 0; j < sudoku.SIZE; j++) {
            // NO FUCKING Clue why this works but it does
            os << static_cast<int>(sudoku.matrix[i][j]) << " ";

            if (j % 3 == 2 && j != sudoku.SIZE - 1) {
                os << "| ";
            }
        }

        os << "\n";

        if (i % 3 == 2 && i != sudoku.SIZE - 1) {
            os << "------+-------+------\n";
        }
    }

    return os;
}

/// 1. Fill all diagonal 3*3 martixs
/// 2. Fill recusrively all non-diagonal matrixes with 'safe' number
/// 3. Once full we remove K elements randomly
void SudokoGrid::__random() noexcept {
    SudokoGrid sudoko = SudokoGrid();

    // Fill the diagonal SIZE number of SIZE x SIZE martixes
    for (uint8_t i = 0;i < SudokoGrid::SIZE;i += SudokoGrid::SUBMARTIX_SIZE) sudoko.fillSubmartix(i,i);
}

void SudokoGrid::fillSubmartix(uint8_t const row,uint8_t const col) noexcept {
    uint8_t number;
    for(uint8_t i = 0;i < SudokoGrid::SUBMARTIX_SIZE;i++) {
        for (uint8_t j = 0;j < SudokoGrid::SUBMARTIX_SIZE;j++) {
            do {
                // Generate Random number
                number = (int) floor((float)(rand() / double(RAND_MAX) * number + 1));
            } while (possibleToPlaceInSubmartix(row,col,number));

            matrix[row + i][col + j] = number;
        }
    }
}

bool SudokoGrid::possibleToPlaceInSubmartix(uint8_t rowStart, uint8_t colStart, uint8_t number) const noexcept{
    for (uint8_t i = 0; i < SudokoGrid::SUBMARTIX_SIZE; i++) {
        for (uint8_t j = 0; j < SudokoGrid::SUBMARTIX_SIZE; j++) {
            if (matrix[rowStart + i][colStart + j] == number) return false;
        }
    }

    return true;
}
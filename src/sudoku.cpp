// soduko.cpp

#include "sudoku.hpp"

std::ostream &operator<<(std::ostream& os,const SudokoGrid& sudoku) {
    for (auto i = 0; i < sudoku.SIZE; i++) {
        for (auto j = 0; j < sudoku.SIZE; j++) {
            os << sudoku.matrix[i][j] << " ";

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

void SudokoGrid::update(int i,int j,int num) noexcept {    
    matrix[i][j] = num;         
}

/// 1. Fill all diagonal 3*3 martixs
/// 2. Fill recusrively all non-diagonal matrixes with 'safe' number
/// 3. Once full we remove K elements randomly
void SudokoGrid::__random(const int missingNumbers) noexcept {     
    SudokoGrid sudoko = SudokoGrid();

    // Fill the diagonal SIZE number of SIZE x SIZE martixes
    for (int i = 0;i < SudokoGrid::SIZE;i += SudokoGrid::SUBMARTIX_SIZE) sudoko.fillSubmartix(i,i);

    fillRemainingMartix(0,SudokoGrid::SUBMARTIX_SIZE);

    removeDigits(missingNumbers);
}

void SudokoGrid::__fromFile(const char* fileName) {
   std::ifstream file(fileName);

    if (!file.is_open()) {
        std::cerr << "Unable to open file: " << fileName << std::endl;
        return; // Return an empty grid if file cannot be opened
    }

    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            if (!(file >> matrix[i][j])) {
                std::cerr << "Error reading file: " << fileName << std::endl;
                return; // Return an incomplete grid if error reading file
            }
        }

        // Check that there are no extra numbers on the line
        std::string restOfLine;
        std::getline(file, restOfLine);
        if (!restOfLine.empty()) {
            std::cerr << "Error: Line " << i + 1 << " contains more than 9 numbers." << std::endl;
            return; // Return an incomplete grid if error in file format
        }
    }

    // Check that there are no extra lines in the file
    std::string extraLine;
    std::getline(file, extraLine);
    if (!extraLine.empty()) {
        std::cerr << "Error: File contains more than 9 lines." << std::endl;
        return; // Return an incomplete grid if error in file format
    }

    // Return the completed grid
}     

int SudokoGrid::randomNumber(const int n) const noexcept {
    return (int) floor((float)(rand() / double(RAND_MAX) * n + 1));
}

int SudokoGrid::countMissingBoxes() const noexcept {
    int missingCount = 0;
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            if (matrix[i][j] == 0) {
                missingCount++;
            }
        }
    }
    return missingCount;
}

void SudokoGrid::fillSubmartix(int const row,int const col) noexcept {
    int number;
    for(int i = 0;i < SudokoGrid::SUBMARTIX_SIZE;i++) {
        for (int j = 0;j < SudokoGrid::SUBMARTIX_SIZE;j++) {
            do {
                // Generate Random number
                number = randomNumber(SIZE);
            } while (!possibleToPlaceInSubmartix(row,col,number));

            matrix[row + i][col + j] = number;
        }
    }
}

bool SudokoGrid::fillRemainingMartix(int i,int j) noexcept {
    if (j >= SudokoGrid::SIZE && i < SudokoGrid::SIZE - 1) {
        i = i + 1;
        j = 0;
    }
    if (i >= SudokoGrid::SIZE && j >= SudokoGrid::SIZE) return true;
    if (i < SudokoGrid::SUBMARTIX_SIZE) {
        if (j < SudokoGrid::SUBMARTIX_SIZE) j = SudokoGrid::SUBMARTIX_SIZE;
    } else if (i < SudokoGrid::SIZE - SudokoGrid::SUBMARTIX_SIZE) {
        if (j == (int)(i / SudokoGrid::SUBMARTIX_SIZE) * SudokoGrid::SUBMARTIX_SIZE) j = j + SudokoGrid::SUBMARTIX_SIZE;
    } else {
        if (j == SudokoGrid::SIZE - SudokoGrid::SUBMARTIX_SIZE) {
            i = i + 1;
            j = 0;
            if (i >= SudokoGrid::SIZE) return true;
        }
    }
    for (int num = 1; num <= SudokoGrid::SIZE; num++) {
        if (isSafe(i, j, num)) {
            matrix[i][j] = num;
            if (fillRemainingMartix(i, j + 1)) return true;
            matrix[i][j] = 0;
        }
    }
    return false;
}

bool SudokoGrid::possibleToPlaceInSubmartix(int rowStart, int colStart, int number) const noexcept {
    for (int i = 0; i < SudokoGrid::SUBMARTIX_SIZE; i++) {
        for (int j = 0; j < SudokoGrid::SUBMARTIX_SIZE; j++) {
            if (matrix[rowStart + i][colStart + j] == number) return false;
        }
    }

    return true;
}

bool SudokoGrid::isSafe(int i,int j,int num) const noexcept {
    return existenceOfRow(i, num) && existenceOfColumn(j, num) && possibleToPlaceInSubmartix(i - i % SudokoGrid::SUBMARTIX_SIZE, j - j % SudokoGrid::SUBMARTIX_SIZE, num);
}

bool SudokoGrid::existenceOfRow(int i, int num) const noexcept {
    for (int j = 0; j < SudokoGrid::SIZE; j++) {
        if (matrix[i][j] == num) return false;
    }
    return true;
}

bool SudokoGrid::existenceOfColumn(int j, int num) const noexcept {
    for (int i = 0; i < SudokoGrid::SIZE; i++) {
        if (matrix[i][j] == num) return false;
    }
    return true;
}

void SudokoGrid::removeDigits(const int missingNumbers) noexcept {
    int count = missingNumbers;
    while (count != 0) {
        int cellId = randomNumber(SIZE * SIZE) - 1;
        // extract coordinates i and j
        int i = cellId / SIZE;
        int j = cellId % SIZE;

        if (j != 0) {
            j = j - 1;
        }

        if (matrix[i][j] != 0) {
            count--;
            matrix[i][j] = 0;
        }
    }
}

bool SudokoGrid::solve() noexcept {
    auto [row,col,box] = applyBitmasks();
    return __solve(row,col,box,0,0);
}


bool SudokoGrid::__solve(
    std::array<int, SudokoGrid::SIZE> row,
    std::array<int, SudokoGrid::SIZE> col,
    std::array<int, SudokoGrid::SIZE> box,
    int i,
    int j
) noexcept {
    if (i == SIZE - 1 && j == SIZE) return true;
    if (j == SIZE) j = 0, i++;
 
    if (matrix[i][j]) return __solve(row,col,box, i, j + 1);

    for (int nr = 1; nr <= SIZE; nr++) {
        if (isSafe(i, j, nr)) {
            //  Assign nr in the current (i, j) position an add nr to each bitmask
            matrix[i][j] = nr;
            row[i] |= 1 << nr;
            col[j] |= 1 << nr;
            box[getBox(i, j)] |= 1 << nr;
 
            if (__solve(row,col,box, i, j + 1))
                return true;
 
            // Remove nr from each bitmask
            // and search for another possibility
            row[i] &= ~(1 << nr);
            col[j] &= ~(1 << nr);
            box[getBox(i, j)] &= ~(1 << nr);
        }

        matrix[i][j] = 0;
    }

    return false;
}

std::tuple<
    std::array<int, SudokoGrid::SIZE>,
    std::array<int, SudokoGrid::SIZE>,
    std::array<int, SudokoGrid::SIZE>
> SudokoGrid::applyBitmasks() noexcept {
    std::array<int, SIZE> row, col, box = {};

    for (int i = 0; i < SudokoGrid::SIZE; i++) {
        for (int j = 0; j < SudokoGrid::SIZE; j++) {
            row[i] |= 1 << matrix[i][j];
            col[j] |= 1 << matrix[i][j];
            box[getBox(i, j)] |= 1 << matrix[i][j];
        }   
    }
        
    return std::make_tuple(row,col,box);
}
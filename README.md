# interactive-sudoku
 This repository includes a console-based interface for interacting with the Sudoku solver program. The solver employs an efficient algorithm to automatically solve Sudoku puzzles of varying difficulty levels. It also allows one to play an interactive console-based on it

## Installation

1. Clone the repository to your local machine:

```bash
   git clone https://github.com/your-username/interactive-sudoku.git
```

2. Navigate to the project directory
3. To build the executable run :
```
    g++ -g "${fileDirname}\\main.cpp" -o ${fileDirname}\\sudoko.exe sudoku.cpp
```

## Usage 

```
Usage: sudoku [OPTIONS]

Options:
  play <N>                 Launch new interactive mode with N numbers missing
  play --custom            Launch new interactive mode with a custom grid
  play --new <FILE_DIR>    Launch interactive mode from a saved game (.sudoku files)
  solve --custom           Launch solve mode with a custom grid
  solve --new <FILE_DIR>   Launch solve mode from a .sudoku file

```

## Examples
- Launch new interactive mode with 30 numbers missing:

```bash
    sudoku play 30
```

- Launch new interactive mode with a custom grid:

```bash
    sudoku play --custom
```

- Launch interactive mode from a saved game:


```bash
    sudoku play --new path/to/your/game.sudoku
```

- Launch solve mode with a custom grid:

```bash
    sudoku solve --custom
```

- Launch solve mode from a saved game:

```bash
    sudoku solve --new path/to/your/game.sudoku
```

## Note 

Ensure that the custom grid or saved game file is formatted correctly, with each row of the Sudoku grid on a new line and each cell. The program will validate the input format. Here is an example

```
530070000
600195000
098000060
800060003
400803001
700020006
060000280
000419005
000080079
```
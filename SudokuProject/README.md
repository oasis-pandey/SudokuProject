# Sudoku Solver Project - VenomDaoistSudokuProjectCS2308SPRING2025

This project is a Sudoku puzzle generator and solver which is implemented in C++. It has mainly two solving algorithms: SolveBoard which is like a bruteforce approach and uses simple backtracking algorithm and a SolveBoardEfficient which uses Minimum Remaining Values(MRV) technique and cleverly selects the sudoku grid with the lowest possible options. At the end,it compares the solveBoard and solveBoardEfficient with different sample sizes.

## Project Overview

This project implements a comprehensive Sudoku puzzle system that can:
- Generate valid Sudoku puzzles using generator.cpp
- Solve Sudoku puzzles using solveBoard and SolveBoardEfficient.
- Compare the performance of solveBoard and SolveBoardEfficient.
- Save and load puzzles and their solutions

## Objectives
- Generate valid Sudoku puzzles and solve them using backtrcking(solveBoard) and MRV technique(solveBoardEfficient).
- Compare the average solving tome of solveBoard and solveBoardEfficient.
- Proper management of memory by dynamically allocating memory, deallocating memory when done, checking for any memory leaks and  dangling pointers.
- Provide DEBUG_MODE for testing and NON-DEBUG_MODE for running the final completed project.


## Features

- **Puzzle Generation**: Generate valid Sudoku puzzles 
- **Multiple Solving Algorithms**: Implement different approaches to solve Sudoku puzzles
- **Performance Comparison**: Compare the efficiency of different solving algorithms
- **File I/O Operations**: Save puzzles and solutions to files 
- **Debug Mode**: Special debug mode for testing and development (comment #define DEBUG_MODE to run the actual program)
- **Configurable Parameters**: Adjust number of puzzles to generate

## Project Structure

```
SudokuProject/
├── include/         # Header files containing documentations for each functions
├── src/             # Source files which contains code for generating, solving, saving, utility functions etc.
├── data/            # Data directory for puzzles and solutions
│   ├── puzzles/     # Generated puzzle files
│   └── solutions/   # Solution files in sorted order
├── main.cpp         # Main program entry point
├── CMakeLists.txt   # CMake build configuration
└── buildrun.sh      # Build and run script 
```


## How to build and run the project?

1. Clone the repository
2. Navigate to the project directory (you can open SudokuProject as root and type in bash buildrun.sh ../SudokuProject/ to run the file)
3. Run the build script:
   ```bash
   buildrun.sh ../SudokuProject/
   ```

The script will:
- Create a build directory
- Configure the project with CMake
- Build the project
- Run the executable

## Usage

The program will:
1. Generate a specified number of Sudoku puzzles
2. Solve the generated puzzles
3. Save both puzzles and solutions to files
4. Run performance comparisons between SolveBoard and SolveBoardEfficient

## Debug Mode

To enable debug mode for testing and development:
1. Uncomment the `#define DEBUG_MODE` line in `main.cpp`
2. Rebuild and run the project (using bash buildrun.sh ../SudokuProject/)

## Contributors
1. Oasis Pandey 
2. Niraj Bhattarai
3. Yojana Luitel
4. Bidhan Paudel 

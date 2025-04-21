/**
 * @file sudoku.h
 * @brief Core Sudoku solving and board generation functions.
 *
 * This header file declares functions essential for solving Sudoku puzzles
 * and validating board states. It includes:
 * - A backtracking Sudoku solver.
 * - A cell validation function to ensure valid number placement.
 * - A board generation stub for creating Sudoku puzzles.
 *
 * All functions operate on dynamically allocated 9x9 Sudoku boards
 * represented as `int**`, where empty cells are denoted by 0.
 *
 * @author
 * Keshav Bhandari
 *
 * @date
 * February 7, 2025
 */

#ifndef SUDOKUPROJECT_SUDOKU_H
#define SUDOKUPROJECT_SUDOKU_H

#include <iostream>

/**
  * TODO: Provide appropriate Documentation, see other examples provided within the projects
  */
 /**
 * @brief Checks whether placing a number is valid on a Sudoku board.
 * 
 * Verifies if the given number `k` can be placed at position (r, c) by ensuring
 * it does not already exist in the same row, column, or 3x3 subgrid.
 * 
 * @param BOARD Pointer to the 2D Sudoku board.
 * @param r Row index of the cell to check.
 * @param c Column index of the cell to check.
 * @param k The number to validate for placement.
 * @return True if placing `k` at (r, c) is valid; otherwise, false.
 */

bool isValid(int** BOARD, const int& r, const int& c, const int& k);

/**
  * TODO: Provide appropriate Documentation, see other examples provided within the projects
  */
 /**
 * @brief Solves a Sudoku board using backtracking.
 * 
 * Recursively fills empty cells starting from (r, c) by trying numbers 1–9 and backtracking when needed.
 * 
 * @param BOARD Pointer to the 2D Sudoku board.
 * @param r Current row index.
 * @param c Current column index.
 * @return True if the board is successfully solved; otherwise, false.
 */

bool solveBoard(int** BOARD, const int& r=0, const int& c=0);

// ========================= Efficient Solutions ==========================


/**
  * TODO: Provide appropriate Documentation, see other examples provided within the projects
  */

  /**
 * @brief Finds the next empty cell using the Minimum Remaining Value (MRV) heuristic.
 * 
 * This function implements the MRV (Minimum Remaining Value) heuristic for Sudoku solving
 * by finding the empty cell that has the fewest valid number options. This optimization
 * helps reduce the branching factor in the backtracking search.
 * 
 * The function:
 * 1. Scans the entire board for empty cells (value == 0)
 * 2. For each empty cell, counts how many valid numbers (1-9) can be placed
 * 3. Tracks the cell with the minimum number of valid options
 * 4. Returns immediately if a cell with only one valid option is found
 * 
 * @param BOARD A pointer to the 9x9 Sudoku board
 * @return std::tuple<int, int, int> containing:
 *         - First element: Row index of the selected cell
 *         - Second element: Column index of the selected cell
 *         - Third element: Number of valid options for that cell
 *         Returns {-1, -1, INT_MAX} if no empty cells are found
 */
std::tuple<int, int, int> findNextCell(int** BOARD);

/**
 * @brief Efficiently solves a Sudoku board using the Minimum Remaining Value (MRV) heuristic.
 * 
 * This function implements an optimized Sudoku solving algorithm that uses the MRV heuristic
 * to reduce the branching factor in the backtracking search. Instead of filling cells in a
 * fixed order (row by row, column by column), it selects the empty cell with the fewest
 * valid number options at each step.
 * 
 * The MRV heuristic significantly improves performance by:
 * 1. Reducing the number of backtracks needed to find a solution
 * 2. Prioritizing cells with fewer options, which are more likely to lead to a solution
 * 3. Providing early exit opportunities when cells with only one valid option are found
 * 
 * The function uses recursive backtracking with the following steps:
 * 1. Find the next cell to fill using the MRV heuristic via findNextCell()
 * 2. If no empty cells remain, the board is solved
 * 3. Try placing numbers 1-9 in the selected cell
 * 4. For each valid number, recursively attempt to solve the rest of the board
 * 5. If a solution is found, return true
 * 6. If no solution is found, backtrack by removing the number and try the next option
 * 7. If no valid number works, return false to trigger further backtracking
 * 
 * @param BOARD A pointer to the 9x9 Sudoku board to be solved
 * @return true if the board is successfully solved, false otherwise
 */
bool solveBoardEfficient(int** BOARD);


/**
 * @brief Solves a Sudoku board using the selected solving strategy.
 * 
 * Chooses between a basic solver and a more efficient solver based on the provided flag.
 * If the `efficient` flag is true, it uses an optimized algorithm; otherwise, it uses a standard recursive approach.
 * 
 * @param board Pointer to the 2D Sudoku board to solve.
 * @param efficient Flag indicating whether to use the efficient solver.
 * @return True if the board was solved successfully; otherwise, false.
 */

bool solve(int** board, const bool& efficient = false);

#endif //SUDOKUPROJECT_SUDOKU_H
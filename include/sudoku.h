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
bool isValid(int** BOARD, const int& r, const int& c, const int& k);

/**
  * TODO: Provide appropriate Documentation, see other examples provided within the projects
  */
bool solveBoard(int** BOARD, const int& r=0, const int& c=0);

// ========================= Efficient Solutions ==========================


/**
  * TODO: Provide appropriate Documentation, see other examples provided within the projects
  */
std::tuple<int, int, int> findNextCell(int** BOARD);
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

bool solveBoardEfficient(int** BOARD);

/**
  * TODO: Provide appropriate Documentation, see other examples provided within the projects
  */
bool solve(int** board, const bool& efficient = false);

#endif //SUDOKUPROJECT_SUDOKU_H
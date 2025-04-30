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
 * @brief Validates if a number can be placed in a specific cell of the Sudoku board.
 *
 * Checks if placing the number `k` at position `(r, c)` would violate any Sudoku rules:
 * - The number must not appear in the same row
 * - The number must not appear in the same column
 * - The number must not appear in the same 3x3 box
 *
 * @param BOARD A pointer to the 2D Sudoku board (int**).
 * @param r Row index of the cell to check.
 * @param c Column index of the cell to check.
 * @param k Number to validate for placement.
 * @return true if the number can be placed at the given position, false otherwise.
 */
bool isValid(int** BOARD, const int& r, const int& c, const int& k);

/**
 * @brief Solves a Sudoku board using backtracking algorithm.
 *
 * Recursively attempts to solve the Sudoku board by trying numbers 1-9
 * in empty cells. The algorithm backtracks when it encounters a dead end.
 * Starts solving from position (r, c) and proceeds row by row.
 *
 * @param BOARD A pointer to the 2D Sudoku board (int**).
 * @param r Starting row index (default: 0).
 * @param c Starting column index (default: 0).
 * @return true if the board is solvable, false otherwise.
 */
bool solveBoard(int** BOARD, const int& r=0, const int& c=0);

// ========================= Efficient Solutions ==========================

/**
 * @brief Finds the next empty cell in the Sudoku board.
 *
 * Scans the board from left to right, top to bottom to find the first
 * empty cell (cell with value 0). Returns the coordinates of the empty cell.
 *
 * @param BOARD A pointer to the 2D Sudoku board (int**).
 * @return std::tuple<int, int, int> A tuple containing (row, column, value) of the empty cell.
 *         If no empty cell is found, returns (-1, -1, -1).
 */
std::tuple<int, int, int> findNextCell(int** BOARD);

/**
 * @brief Solves a Sudoku board using an optimized backtracking algorithm.
 *
 * Uses a more efficient approach by:
 * 1. Finding the next empty cell using findNextCell
 * 2. Trying numbers 1-9 in the empty cell
 * 3. Recursively solving the rest of the board
 * 4. Backtracking when necessary
 *
 * @param BOARD A pointer to the 2D Sudoku board (int**).
 * @return true if the board is solvable, false otherwise.
 */
bool solveBoardEfficient(int** BOARD);

/**
 * @brief Solves a Sudoku board using either the standard or efficient solver.
 *
 * Provides a unified interface to solve Sudoku boards using either the
 * standard backtracking algorithm or the optimized version.
 *
 * @param board A pointer to the 2D Sudoku board (int**).
 * @param efficient Flag to choose between standard (false) and efficient (true) solver.
 * @return true if the board is solvable, false otherwise.
 */
bool solve(int** board, const bool& efficient = false);

#endif //SUDOKUPROJECT_SUDOKU_H
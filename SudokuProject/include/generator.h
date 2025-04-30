/**
* @file generator.h
 * @brief Function prototypes for generating random solvable Sudoku boards.
 *
 * This header defines functions to:
 * - Create empty Sudoku boards.
 * - Fill independent diagonal boxes.
 * - Solve and generate a complete Sudoku board.
 * - Randomly delete cells to create a solvable puzzle.
 * - Generate a complete Sudoku puzzle with a specific number of empty cells.
 *
 * Detailed function descriptions and parameters are provided below.
 *
 * @author
 * Keshav Bhandari
 *
 * @date
 * February 7, 2025
 */

#ifndef GENERATOR_H
#define GENERATOR_H

#include <vector>

/**
 * @brief Creates and returns a new empty 9x9 Sudoku board.
 *
 * Allocates memory for a 9x9 Sudoku board and initializes all cells to 0.
 * The board is represented as a 2D array of integers, where 0 represents an empty cell.
 *
 * @return int** A dynamically allocated 9x9 Sudoku board with all cells set to 0.
 * @note The caller is responsible for freeing the allocated memory.
 */
int** getEmptyBoard();

/**
 * @brief Generates a vector of numbers 1-9 in random order.
 *
 * Creates a vector containing numbers 1 through 9 and shuffles them
 * using a random number generator. The shuffled vector can be used to fill Sudoku
 * boxes with unique numbers in a random order.
 *
 * @return std::vector<int> A vector containing numbers 1-9 in random order.
 */
std::vector<int> getShuffledVector();

/**
 * @brief Fills the three diagonal 3x3 boxes of a Sudoku board with random numbers.
 *
 * Fills the three diagonal 3x3 boxes (top-left, center, and bottom-right)
 * with unique numbers from 1 to 9 in random order. The diagonal boxes are independent
 * of each other, meaning they can be filled without checking for conflicts.
 *
 * @param BOARD A 9x9 Sudoku board to be filled.
 * @note The board should be empty (all cells set to 0) before calling this function.
 */
void fillBoardWithIndependentBox(int** BOARD);

/**
 * @brief Randomly deletes a specified number of cells from a Sudoku board.
 *
 * Randomly selects and clears (sets to 0) a specified number of cells
 * from the Sudoku board. The selection is truly random, and each cell can be selected
 * only once. The function ensures that the specified number of cells is valid
 * (between 1 and 81) and that the board pointer is not null.
 *
 * @param BOARD A 9x9 Sudoku board from which cells will be deleted.
 * @param n The number of cells to delete (must be between 1 and 81).
 * @throw std::invalid_argument If BOARD is null or n is not between 1 and 81.
 */
void deleteRandomItems(int** BOARD, const int& n);

/**
 * @brief Generates a solvable Sudoku puzzle with a specified number of empty cells.
 *
 * Creates a complete Sudoku puzzle by:
 * 1. Creating an empty board
 * 2. Filling the diagonal boxes with random numbers
 * 3. Solving the board to completion
 * 4. Randomly removing the specified number of cells
 *
 * The resulting board is guaranteed to be solvable and contains the specified
 * number of empty cells.
 *
 * @param empty_boxes The number of cells to be emptied in the generated puzzle.
 * @return int** A dynamically allocated 9x9 Sudoku board with the specified number of empty cells.
 * @note The caller is responsible for freeing the allocated memory.
 */
int** generateBoard(const int& empty_boxes);

#endif // GENERATOR_H

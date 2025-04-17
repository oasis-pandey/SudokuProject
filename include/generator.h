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
 * @brief Creates and initializes an empty 9x9 Sudoku board.
 * 
 * This function dynamically allocates memory for a 9x9 Sudoku board
 * and initializes all cells to 0, representing empty cells.
 * 
 * @return A pointer to a 2D array representing an empty Sudoku board.
 *         The caller is responsible for freeing the allocated memory.
 */
int** getEmptyBoard();

/**
 * @brief shuffles a array containing number 1 to 9
 * 
 * This function shuffles a vector of integers from number 1 to 9 randomly which will later 
 * be used to fill up the board.
 * It generates a random number from a hardware-based source. It might be time, cpu clock 
 * speed, temperature readings etc.
 * mt19937 is a Mersenne Twister random number generator fast and high-quality
 * randomness. The seed (rd()) ensures different random outputs in each execution.
 * 
 * @return A shuffled vector of integers from number 1 to 9. 
 * 
 */
std::vector<int> getShuffledVector();

/**
 * @brief Fills the three diagonal 3x3 boxes of a Sudoku board with unique numbers.
 * 
 * This function fills the three independent diagonal boxes (top-left, center, and bottom-right)
 * of a Sudoku board with unique numbers from 1 to 9. The numbers are randomly shuffled
 * using getShuffledVector() to ensure different patterns in each execution.
 * 
 * @param BOARD A pointer to a 9x9 Sudoku board to be filled.
 *              The board should be initialized with getEmptyBoard().
 */
void fillBoardWithIndependentBox(int** BOARD);

/**
 * @brief Randomly deletes a specified number of cells from a Sudoku board.
 * 
 * This function randomly selects and clears (sets to 0) a specified number of cells
 * from the Sudoku board. The selection is done using a uniform distribution to ensure
 * random distribution across the board.
 * 
 * @param BOARD A pointer to a 9x9 Sudoku board.
 * @param n The number of cells to delete (should be between 1 and 81).
 *          For a balanced challenge, typically around 40-45 cells are deleted.
 */
void deleteRandomItems(int** BOARD, const int& n);

/**
 * @brief Generates a complete, solvable Sudoku puzzle with a specified number of empty cells.
 * 
 * This function creates a complete Sudoku puzzle by:
 * 1. Creating an empty board
 * 2. Filling the diagonal boxes with unique numbers
 * 3. Solving the board to create a complete solution
 * 4. Randomly deleting the specified number of cells
 * 
 * @param empty_boxes The number of cells to leave empty in the final puzzle.
 *                    For a balanced challenge, typically between 40-45 cells.
 * @return A pointer to a 9x9 Sudoku board with the specified number of empty cells.
 *         The caller is responsible for freeing the allocated memory.
 */
int** generateBoard(const int& empty_boxes);

#endif // GENERATOR_H

/**
 * @file sudoku.cpp
 * @brief Implementation of core Sudoku solving and validation functions.
 *
 * Contains the logic for validating moves and solving Sudoku puzzles using
 * a backtracking algorithm. Detailed function descriptions are provided in
 * the corresponding header file.
 *
 * @author
 * Keshav Bhandari
 *
 * @date
 * February 7, 2025
*/

#include "../include/sudoku.h"
#include <iostream>
#include <tuple>
using namespace std;

bool isValid(int** BOARD, const int& r, const int& c, const int& k)
{
    // Check if 'k' already exists in the same row or column
    for (int i = 0; i < 9; i++)
    {
        if (k == BOARD[r][i] || k == BOARD[i][c])
            return false;  // Invalid placement
    }

    // Determine starting indices for the 3x3 subgrid
    int startRow = 3 * (r / 3);
    int startCol = 3 * (c / 3);

    // Check if 'k' exists in the 3x3 subgrid
    for (int i = startRow; i < startRow + 3; i++)
    {
        for (int j = startCol; j < startCol + 3; j++)
        {
            if (k == BOARD[i][j])
                return false;  // Invalid placement
        }
    }

    return true;  // Placement is valid
}

bool solveBoard(int** BOARD, const int& r, const int& c)
{
    // If we've reached beyond the last row, the board is solved
    if (r == 9)
        return true;

    // Move to the next row if we've reached the end of the current row
    if (c == 9)
        return solveBoard(BOARD, r + 1, 0);

    // Skip already filled cells and move to the next column
    if (BOARD[r][c] != 0)
        return solveBoard(BOARD, r, c + 1);

    // Try placing numbers 1 to 9 in the current empty cell
    for (int k = 1; k <= 9; k++)
    {
        if (isValid(BOARD, r, c, k))
        {
            BOARD[r][c] = k;  // Place number 'k'

            // Recursively attempt to solve the rest of the board
            if (solveBoard(BOARD, r, c + 1))
                return true;  // Found a valid solution

            // Backtrack: Remove the number if no solution is found
            BOARD[r][c] = 0;
        }
    }

    // Trigger backtracking if no valid number can be placed
    return false;
}



tuple<int, int, int> findNextCell(int** BOARD) {
    int minOptions = 10; // More than maximum possible (9)
    int bestRow = -1, bestCol = -1;

    for (int r = 0; r < 9; r++) {
        for (int c = 0; c < 9; c++) {
            if (BOARD[r][c] == 0) {  // Check if cell is empty
                int optionsCount = 0;
                for (int k = 1; k <= 9; k++) {
                    if (isValid(BOARD, r, c, k)) {
                        optionsCount++;
                    }
                }
                
                // If we find a cell with no valid options, the board is unsolvable
                if (optionsCount == 0) {
                    return {r, c, 0}; // Immediately signal an unsolvable state
                }
                
                // Update best cell if this one has fewer options
                if (optionsCount < minOptions) {
                    minOptions = optionsCount;
                    bestRow = r;
                    bestCol = c;
                    
                    // Early exit is optional but can improve performance
                    if (optionsCount == 1) {
                        return {r, c, 1};
                    }
                }
            }
        }
    }
    return {bestRow, bestCol, minOptions};
}

bool solveBoardEfficient(int** BOARD) {
    // Get the next cell to fill using MRV heuristic
    auto [row, col, options] = findNextCell(BOARD);
    
    // If no empty cells are found (row == -1), the board is solved
    if (row == -1) {
        return true;
    }
    
    // If a cell has no valid options (options == 0), the board is unsolvable
    if (options == 0) {
        return false;
    }
    
    // Try placing numbers 1 to 9 in the selected cell
    for (int k = 1; k <= 9; k++) {
        if (isValid(BOARD, row, col, k)) {
            // Place the number
            BOARD[row][col] = k;
            
            // Recursively try to solve the rest of the board
            if (solveBoardEfficient(BOARD)) {
                return true;  // Solution found
            }
            
            // Backtrack: remove the number if no solution is found
            BOARD[row][col] = 0;
        }
    }
    
    // No valid number fits in this cell, trigger backtracking
    return false;
}


bool solve(int** board, const bool& efficient) {
    // TODO: Implement logic to select the appropriate solver based on the 'efficient' flag

    /**
     * - If efficient == true, return solveBoardEfficient(board).
     * - Else, return solveBoard(board, 0, 0).
     */

    if (efficient == true){
        return solveBoardEfficient(board);
    }else{
        return solveBoard(board, 0, 0);
    }
}
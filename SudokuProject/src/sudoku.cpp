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
    int minOptions = 10; // More than max i.e 9
    int bestRow = -1, bestCol = -1;

    for (int r = 0; r < 9; r++) {
        for (int c = 0; c < 9; c++) {
            if (BOARD[r][c] == 0) {  
                int optionsCount = 0;
                for (int k = 1; k <= 9; k++) {
                    if (isValid(BOARD, r, c, k)) {
                        optionsCount++;
                    }
                }
                
                
                if (optionsCount == 0) {
                    return {r, c, 0};
                }
                
                
                if (optionsCount < minOptions) {
                    minOptions = optionsCount;
                    bestRow = r;
                    bestCol = c;
                    
                    
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
    
    auto [row, col, options] = findNextCell(BOARD);
    
    
    if (row == -1) {
        return true;
    }
    
    
    if (options == 0) {
        return false;
    }
    
    
    for (int k = 1; k <= 9; k++) {
        if (isValid(BOARD, row, col, k)) {
            
            BOARD[row][col] = k;
            
            
            if (solveBoardEfficient(BOARD)) {
                return true;  
            }
            
            
            BOARD[row][col] = 0;
        }
    }
    
    
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
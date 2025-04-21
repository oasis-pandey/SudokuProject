//
// Created by Keshav Bhandari on 2/7/24.
//
#include <iostream>
#include <filesystem>
#include <fstream>
#include <string>
#include <vector>
#include <regex>
#include <chrono>
#include <iomanip>  // For formatted output

#include "../include/generator.h"
#include "../include/sudoku_io.h"
#include "../include/utils.h"
#include "../include/sudoku.h"

using namespace std;
using namespace std::chrono;

void printBoard(int** BOARD, const int& r, const int& c, int k)
{
    if(BOARD[r][c]>0) k = 0;

    for (int i = 0; i < 9; i++)
    {
        for (int j = 0; j < 9; j++)
        {
            string board_piece;
            if (BOARD[i][j] == 0) board_piece = "\x1B[93m-\x1B[0m"; // Yellow
            else board_piece = to_string(BOARD[i][j]); // White
            if ((i == r && j == c) && k != 0)
            {
                if (isValid(BOARD, r, c, k))
                    board_piece = "\x1B[32m" + to_string(k) + "\x1B[0m"; // Green
                else
                    board_piece = "\x1B[31m" + to_string(k) + "\x1B[0m"; // Red
            }
            cout << board_piece;
            if (j == 2 || j == 5) cout << " | ";
            else cout << " ";
        }
        if (i == 2 || i == 5)
        {
            cout << endl;
            for (int l = 0; l < 21; l++) cout << ".";
        }
        cout << endl;
    }
}

void boardToString(int** BOARD, string &content){
    for(int i = 0; i < 9; i++){
        for(int j = 0; j < 9; j++){
            string board_piece;

            if (BOARD[i][j] == 0) content += "-";
            else content += to_string(BOARD[i][j]);

            if (j == 2 || j == 5)  content += " | ";
            else content += " ";
        }
        if (i == 2 || i == 5)
        {
            content += "\n";
            for (int l = 0; l < 21; l++) content += ".";
        }
        content += "\n";
    }
}

bool writeSudokuToFile(int** BOARD, const string& filename) {
    string content;
    boardToString(BOARD, content);
    ofstream outFile(filename); // Open file for writing
    if (outFile.is_open()) {
        outFile << content; // Write content to file
        outFile.close(); // Close the file
        cout << "Content has been written to the file: " << filename << endl;
        return true;
    }
    cerr << "Unable to open file: " << filename << endl;
    return false;
}

void replaceCharacter(std::string& str, char oldChar, char newChar) {
    for (char &ch: str) {
        if (ch == oldChar) {
            ch = newChar;
        }
    }
}

void extractNumbers(const string& input, vector<int>& numbers) {
    regex regex("\\d+");

    auto iterator = sregex_iterator(input.begin(), input.end(), regex);
    auto end = sregex_iterator();

    for (; iterator != end; ++iterator) {
        numbers.push_back(stoi(iterator->str()));
    }
}

void fillBoard(const vector<int>& numbers, int **BOARD){
    for(int i = 0; i < 9; i++) {
        BOARD[i] = new int[9];
        for(int j = 0; j < 9; j++){
            BOARD[i][j] = numbers[i * 9 + j];
        }
    }
}

int** readSudokuFromFile(const string& filename){
    int** BOARD = new int*[9];
    vector<int> numbers;

    ifstream file(filename);
    string sudoku = string(istreambuf_iterator<char>(file), istreambuf_iterator<char>());

    replaceCharacter(sudoku, '-', '0');
    extractNumbers(sudoku, numbers);
    fillBoard(numbers, BOARD);
    return BOARD;
}

bool checkIfSolutionIsValid(int** BOARD){
    for(int r = 0; r < 9; r++) {
        for(int c = 0; c < 9; c++) {
            int k = BOARD[r][c];
            BOARD[r][c] = 0;
            if(!isValid(BOARD, r, c, k)){
                BOARD[r][c] = k;
                // cout << "!!!!!!!!!!!!!!!! TEST FAILED !!!!!!!!!!!!!!!!" << endl;
                return false;
            }
            BOARD[r][c] = k;
        }
    }
    // cout << "--------------- TEST PASSED ---------------" << endl;
    return true;
}

vector<string> getAllSudokuInFolder(const string& folderPath){
    vector<std::string> sudokus;
    for (const auto& entry : filesystem::directory_iterator(folderPath)) {
        if (filesystem::is_regular_file(entry)) {
            sudokus.push_back(entry.path().string());
        }
    }
    cout << sudokus.size() << " Sudoku Puzzle found @ " << folderPath << endl;
    cout << setfill('-') << setw(55)<< "" << setfill(' ') <<endl;
    cout << setw(5) << "Index" << setw(50) << "File Name" << endl;
    cout << setfill('-') << setw(55)<< "" << setfill(' ') <<endl;
    for(int i = 0; i < sudokus.size(); i++)
        cout << setw(5) << i << setw(50) << sudokus[i] << endl;
    cout << setfill('-') << setw(55)<< "" << setfill(' ') <<endl;
    return sudokus;
}

void createAndSaveNPuzzles(const int& num_puzzles, const int& complexity_empty_boxes, const string& destination, const string& prefix){
    /**
     * TODO:
     * - Identify where in this function dynamically allocated memory (e.g., Sudoku boards) should be deallocated.
     * - Use the `deallocateBoard()` function to free memory when:
     *   1. The board is no longer needed (e.g., after solving or processing).
     *   2. Before reassigning a pointer to a new board to avoid memory leaks.
     *   3. Before returning from the function to ensure all allocated memory is freed.
     *
     * Example:
     *   deallocateBoard(BOARD);  // Free memory allocated for the board
     *
     * Hints:
     * - Always deallocate after you're done using the board.
     * - Be mindful of potential memory leaks if the board isn't deallocated properly.
     * - Set the pointer to nullptr after deallocation to avoid dangling pointers.
     */
    int total_success = 0;
    for(int i=0; i < num_puzzles; i++){
        int** BOARD = generateBoard(complexity_empty_boxes);
        string filename = getFileName(i, destination, prefix);
        if(writeSudokuToFile(BOARD, filename)){
            total_success++;
            cout << "Successfully written(" << filename << ") "<< total_success << "of " << num_puzzles << endl;
        }else{
            cout << "!! Failed to write(" << filename << ") "<< total_success << "of " << num_puzzles << endl;
        }
        deallocateBoard(BOARD,9);
    }
    cout << total_success << " files written out of " << num_puzzles <<endl;
}


// Function to display a progress bar in the console
void displayProgressBar(int current, int total, int barWidth = 50) {
    float progress = static_cast<float>(current) / total;
    int pos = static_cast<int>(barWidth * progress);

    cout << "\r[";
    for (int i = 0; i < barWidth; ++i) {
        if (i < pos) cout << "=";
        else if (i == pos) cout << ">";
        else cout << " ";
    }
    cout << "] " << setw(3) << int(progress * 100.0) << "%";
    cout.flush();
}

void solveAndSaveNPuzzles(const int &num_puzzles, const string& source, const string& destination, const string& prefix){
    int total_success_solve = 0;
    int total_success_write = 0;
    vector<string> path_to_sudokus = getAllSudokuInFolder(source);

    cout << "Number of loaded puzzles:" << path_to_sudokus.size() << "/" << num_puzzles << endl;
    for(int i = 0; i < path_to_sudokus.size(); i++){
        int** sudoku = readSudokuFromFile(path_to_sudokus[i]);
        if(solve(sudoku)){
            if(checkIfSolutionIsValid(sudoku)){
                total_success_solve++;
                string filename = getFileName(i, destination, prefix);
                cout << "Puzzle Solved(over available): " << total_success_solve << "/" << path_to_sudokus.size() << " | ";
                cout << "Puzzle Solved(over total): " << total_success_solve << "/" << num_puzzles << endl;
                if(writeSudokuToFile(sudoku, filename)){
                    total_success_write++;
                }
                cout << "Puzzle Solved Written(over available): " << total_success_write << "/" << path_to_sudokus.size() << " | ";
                cout << "Puzzle Solved Written(over total): " << total_success_write << "/" << num_puzzles << endl;
            }
        }
        deallocateBoard(sudoku,9);
    }
}


/**
 * @brief Performs a deep copy of a 9x9 Sudoku board.
 *
 * @param original The original 9x9 Sudoku board to copy.
 * @return int** A pointer to the newly allocated deep-copied board.
 */
int** deepCopyBoard(int** original) {
    // Allocate memory for the new board
    int** newBoard = new int*[9];
    for (int i = 0; i < 9; i++) {
        newBoard[i] = new int[9];  // Allocate each row

        // Copy each element from the original board
        for (int j = 0; j < 9; j++) {
            newBoard[i][j] = original[i][j];
        }
    }
    return newBoard;
}

void compareSudokuSolvers(const int& experiment_size, const int& empty_boxes) {
    cout << "\n=== Comparing Sudoku Solvers ===" << endl;
    cout << "Experiment Size: " << experiment_size << endl;
    cout << "Empty Boxes: " << empty_boxes << endl;
    cout << setfill('-') << setw(60) << "" << setfill(' ') << endl;
    
    // Initialize timing variables
    double total_standard_time = 0.0;
    double total_efficient_time = 0.0;
    int successful_standard = 0;
    int successful_efficient = 0;
    
    // Run experiments
    for (int i = 0; i < experiment_size; i++) {
        // Generate a new board for testing
        int** board1 = generateBoard(empty_boxes);
        int** board2 = deepCopyBoard(board1);
        
        // Time standard solver
        auto start_standard = high_resolution_clock::now();
        bool standard_solved = solveBoard(board1, 0, 0);
        auto stop_standard = high_resolution_clock::now();
        auto duration_standard = duration_cast<microseconds>(stop_standard - start_standard);
        
        // Time efficient solver
        auto start_efficient = high_resolution_clock::now();
        bool efficient_solved = solveBoardEfficient(board2);
        auto stop_efficient = high_resolution_clock::now();
        auto duration_efficient = duration_cast<microseconds>(stop_efficient - start_efficient);
        
        // Update statistics
        if (standard_solved) {
            total_standard_time += duration_standard.count();
            successful_standard++;
        }
        if (efficient_solved) {
            total_efficient_time += duration_efficient.count();
            successful_efficient++;
        }
        
        // Clean up
        deallocateBoard(board1, 9);
        deallocateBoard(board2, 9);
        
        // Display progress
        displayProgressBar(i + 1, experiment_size);
    }
    cout << endl;  // New line after progress bar
    
    // Calculate averages
    double avg_standard_time = successful_standard > 0 ? total_standard_time / successful_standard : 0;
    double avg_efficient_time = successful_efficient > 0 ? total_efficient_time / successful_efficient : 0;
    
    // Display results
    cout << "\nResults:" << endl;
    cout << setfill('-') << setw(60) << "" << setfill(' ') << endl;
    cout << setw(20) << "Metric" << setw(20) << "Standard" << setw(20) << "Efficient" << endl;
    cout << setfill('-') << setw(60) << "" << setfill(' ') << endl;
    
    cout << setw(20) << "Success Rate" 
         << setw(20) << (static_cast<double>(successful_standard) / experiment_size * 100) << "%"
         << setw(20) << (static_cast<double>(successful_efficient) / experiment_size * 100) << "%" << endl;
    
    cout << setw(20) << "Avg Time (μs)" 
         << setw(20) << fixed << setprecision(2) << avg_standard_time
         << setw(20) << fixed << setprecision(2) << avg_efficient_time << endl;
    
    if (avg_standard_time > 0 && avg_efficient_time > 0) {
        double speedup = avg_standard_time / avg_efficient_time;
        cout << setw(20) << "Speedup Factor" 
             << setw(20) << "1.00x" 
             << setw(20) << fixed << setprecision(2) << speedup << "x" << endl;
    }
    
    cout << setfill('-') << setw(60) << "" << setfill(' ') << endl;
}
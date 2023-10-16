#include <iostream>
#include <vector>

using namespace std;

const int N = 9;  // Size of the Sudoku grid

// Function to print the Sudoku grid
void printSudoku(vector<vector<int>> &grid) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            cout << grid[i][j] << " ";
        }
        cout << endl;
    }
}

// Function to check if a number can be placed in a specific cell
bool canPlace(vector<vector<int>> &grid, int row, int col, int num) {
    // Check the row
    for (int i = 0; i < N; i++) {
        if (grid[row][i] == num) {
            return false;
        }
    }

    // Check the column
    for (int i = 0; i < N; i++) {
        if (grid[i][col] == num) {
            return false;
        }
    }

    // Check the 3x3 grid
    int startRow = row - row % 3;
    int startCol = col - col % 3;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (grid[i + startRow][j + startCol] == num) {
                return false;
            }
        }
    }

    return true;
}

// Sudoku solver using backtracking
bool solveSudoku(vector<vector<int>> &grid) {
    int row, col;
    bool isEmpty = false;
    
    for (row = 0; row < N; row++) {
        for (col = 0; col < N; col++) {
            if (grid[row][col] == 0) {
                isEmpty = true;
                break;
            }
        }
        if (isEmpty) {
            break;
        }
    }

    if (!isEmpty) {
        return true;  // No empty cells, Sudoku is solved
    }

    for (int num = 1; num <= N; num++) {
        if (canPlace(grid, row, col, num)) {
            grid[row][col] = num;
            if (solveSudoku(grid)) {
                return true;
            }
            grid[row][col] = 0;  // Backtrack
        }
    }

    return false;
}

int main() {
    vector<vector<int>> grid(N, vector<int>(N));

    cout << "Enter the Sudoku puzzle (0 for empty cells, row by row):\n";
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            cin >> grid[i][j];
        }
    }

    if (solveSudoku(grid)) {
        cout << "Sudoku solution:\n";
        printSudoku(grid);
    } else {
        cout << "No solution exists.\n";
    }

    return 0;
}

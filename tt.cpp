#include<iostream>
#include<vector>
#define size 4
using namespace std;

vector<int> top_clues = { 3,3,1,2};
vector<int> bottom_clues = { 2,1,2,3};
vector<int> left_clues = { 3,2,1,2};
vector<int> right_clues = { 2,1,3,3 };

// Function declarations
bool numberInColumn(int** board, int number, int column);
bool numbrInRow(int** board, int number, int row);
/*void fillFourColumn(int** board, int column, int quarter);
void fillFourRow(int** board, int row, int quarter);
void fillOne(int board[][size], int row, int column);*/
bool isValidPosition(int** board, int row, int column, int number);
bool satisfiesClues(int** board);
bool solver(int** board);
void printboard(int** board);

int main() {
    // Initialize grid
    int** grid = new int* [size];
    for (int i = 0; i < size; i++) {
        grid[i] = new int[size];
        for (int j = 0; j < size; j++) {
            grid[i][j] = 0; // Initialize with zeros
        }
    }

    // Solve the puzzle
    if (solver(grid)) {
        // Print the solved board
        printboard(grid);
    }
    else {
        cout << "no solution exists" << endl;
    }

    // Deallocate memory
    for (int i = 0; i < size; i++) {
        delete[] grid[i];
    }
    delete[] grid;

    return 0;
}

// Function definitions

bool numberInColumn(int** board, int number, int column) {
    for (int i = 0; i < size; i++) {
        if (board[i][column] == number) {
            return true;
        }
    }
    return false;
}

bool numbrInRow(int** board, int number, int row) {
    for (int i = 0; i < size; i++) {
        if (board[row][i] == number) {
            return true;
        }
    }
    return false;
}

/*void fillFourColumn(int** board, int column, int quarter) {
    int value = 1;
    if (quarter == 1) {
        for (int i = 0; i < size; i++) {
            board[i][column] = value++;
        }
    }
    else if (quarter == 2) {
        for (int i = 3; i >= 0; i--) {
            board[i][column] = value++;
        }
    }
}*/

/*void fillFourRow(int** board, int row, int quarter) {
    int value = 1;
    if (quarter == 3) {
        for (int i = 0; i < size; i++) {
            board[row][i] = value++;
        }
    }
    else if (quarter == 4) {
        for (int i = 3; i >= 0; i--) {
            board[row][i] = value++;
        }
    }
}*/

/*void fillOne(int board[][size], int row, int column) {
    board[row][column] = 4;
}*/

bool isValidPosition(int** board, int row, int column, int number) {
    return (!numberInColumn(board, number, column) && !numbrInRow(board, number, row));
}

bool satisfiesClues(int** board) {
    for (int i = 0; i < size; i++) {
        // Check top clues
        int max_height = 0, visible_count = 0;
        for (int j = 0; j < size; j++) {
            if (board[j][i] > max_height) {
                max_height = board[j][i];
                visible_count++;
            }
        }
        if (visible_count != top_clues[i] && top_clues[i] != 0) return false;

        // Check bottom clues
        max_height = 0, visible_count = 0;
        for (int j = size - 1; j >= 0; j--) {
            if (board[j][i] > max_height) {
                max_height = board[j][i];
                visible_count++;
            }
        }
        if (visible_count != bottom_clues[i] && bottom_clues[i] != 0) return false;

        // Check left clues
        max_height = 0, visible_count = 0;
        for (int j = 0; j < size; j++) {
            if (board[i][j] > max_height) {
                max_height = board[i][j];
                visible_count++;
            }
        }
        if (visible_count != left_clues[i] && left_clues[i] != 0) return false;

        // Check right clues
        max_height = 0, visible_count = 0;
        for (int j = size - 1; j >= 0; j--) {
            if (board[i][j] > max_height) {
                max_height = board[i][j];
                visible_count++;
            }
        }
        if (visible_count != right_clues[i] && right_clues[i] != 0) return false;
    }
    return true;
}

bool solver(int** board) {
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            if (board[i][j] == 0) {
                for (int value = 1; value <= size; value++) {
                    if (isValidPosition(board, i, j, value)) {
                        board[i][j] = value;
                        if (solver(board) && satisfiesClues(board)) {
                            return true;
                        }
                        else {
                            board[i][j] = 0;
                        }
                    }
                }
                return false;
            }
        }
    }
    return true;
}

void printboard(int** board) {
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            cout << board[i][j] << " ";
        }
        cout << endl;
    }
}

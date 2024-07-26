#include <iostream>
#include <ctime>
#include <cstdlib>

using namespace std;

const int x = 9;
const int y = 9;

// Function to display the board
void displayBoard(int grid[x][y], bool mines[x][y], bool revealed[x][y]) {
    for (int i = 0; i < x; i++) {
        for (int j = 0; j < y; j++) {
            if (revealed[i][j]) {
                if (mines[i][j]) {
                    cout << " * "; // Mine
                } else {
                    cout << " " << grid[i][j] << " "; // Safe cell with number
                }
            } else {
                cout << " - "; // Hidden cell
            }
        }
        cout << endl;
    }
}

// Function to place mines randomly on the board
void placeMines(bool mines[x][y], int numMines = 10) {
    int minesPlaced = 0;
    srand(time(0));
    while (minesPlaced < numMines) {
        int k = rand() % x;
        int s = rand() % y;
        if (!mines[k][s]) {
            mines[k][s] = true;
            minesPlaced++;
        }
    }
}

// Function to place random numbers on the board in non-mine cells
void placeNumbers(int grid[x][y], bool mines[x][y]) {
    srand(time(0));
    for (int i = 0; i < x; i++) {
        for (int j = 0; j < y; j++) {
            if (!mines[i][j]) { // Don't overwrite mines
                grid[i][j] = rand() % 10; // Random number between 1 and 10
            }
        }
    }
}

// Main game function
int main() {
    int grid[x][y] = {0}; // Use int for grid to store numbers
    bool mines[x][y] = {false}; // Separate array to store mine locations
    bool revealed[x][y] = {false};
    int numMines = 10;
    int score = 0;

    placeMines(mines, numMines); // Place mines
    placeNumbers(grid, mines); // Place random numbers

    while (true) {
        displayBoard(grid, mines, revealed); // Display the board
        int row, col;
        cout << "Enter coordinates to reveal (row col): ";
        cin >> row >> col;

        if (row < 0 || row >= x || col < 0 || col >= y) {
            cout << "Invalid coordinates. Try again." << endl;
            continue;
        }

        if (mines[row][col]) {
            cout << "Game Over! You hit a mine." << endl;
            break;
        } else {
            if (!revealed[row][col]) {
                revealed[row][col] = true;
                score += grid[row][col]; // Add the number to the score
                cout << "Safe! Your score: " << score << endl;
            } else {
                cout << "This cell is already revealed. Try a different cell." << endl;
            }
        }
    }

    cout << "Final score: " << score << endl;

    return 0;
}


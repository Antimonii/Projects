#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>

using namespace std;

const int BOARD_SIZE = 8;
const int NUM_PLAYERS = 2;
const int NUM_SHIPS = 3;
const int SHIP_SIZES[NUM_SHIPS] = {3, 4, 5};

class BattleshipGame {
private:
    char boards[NUM_PLAYERS][BOARD_SIZE][BOARD_SIZE];
    vector<pair<int, int>> ships[NUM_PLAYERS];

public:
    BattleshipGame() {
        for (int i = 0; i < NUM_PLAYERS; ++i) {
            initializeBoard(i);
            placeShips(i);
        }
    }

    void initializeBoard(int playerIndex) {
        for (int i = 0; i < BOARD_SIZE; ++i) {
            for (int j = 0; j < BOARD_SIZE; ++j) {
                boards[playerIndex][i][j] = '.';
            }
        }
    }

    void placeShips(int playerIndex) {
        srand(time(0));
        for (int i = 0; i < NUM_SHIPS; ++i) {
            int row, col;
            bool validPlacement;

            do {
                row = rand() % BOARD_SIZE;
                col = rand() % BOARD_SIZE;
                validPlacement = checkValidPlacement(playerIndex, row, col, SHIP_SIZES[i], true);
            } while (!validPlacement);

            for (int j = 0; j < SHIP_SIZES[i]; ++j) {
                ships[playerIndex].push_back(make_pair(row + j, col));
                boards[playerIndex][row + j][col] = 'S';
            }
        }
    }

    bool checkValidPlacement(int playerIndex, int row, int col, int size, bool horizontal) {
        if (horizontal) {
            if (col + size > BOARD_SIZE) {
                return false;
            }
            for (int j = col; j < col + size; ++j) {
                if (boards[playerIndex][row][j] == 'S') {
                    return false;
                }
            }
        } else {
            if (row + size > BOARD_SIZE) {
                return false;
            }
            for (int i = row; i < row + size; ++i) {
                if (boards[playerIndex][i][col] == 'S') {
                    return false;
                }
            }
        }
        return true;
    }

    void printBoard(int playerIndex) {
        for (int i = 0; i < BOARD_SIZE; ++i) {
            for (int j = 0; j < BOARD_SIZE; ++j) {
                cout << boards[playerIndex][i][j] << " ";
            }
            cout << endl;
        }
    }

    void playGame() {
        int currentPlayer = 0;

        cout << "Welcome to Battleship!" << endl;

        while (true) {
            int row, col;

            cout << "Player " << currentPlayer + 1 << "'s turn." << endl;
            cout << "Enter row and column to guess (0-" << BOARD_SIZE - 1 << "): ";
            cin >> row >> col;

            if (row < 0 || row >= BOARD_SIZE || col < 0 || col >= BOARD_SIZE) {
                cout << "Invalid input. Try again." << endl;
                continue;
            }

            if (boards[currentPlayer][row][col] == 'X' || boards[currentPlayer][row][col] == '*') {
                cout << "You already guessed this location. Try again." << endl;
                continue;
            }

            bool hit = false;
            for (int i = 0; i < NUM_PLAYERS; ++i) {
                if (i != currentPlayer) {
                    for (const auto& ship : ships[i]) {
                        if (ship.first == row && ship.second == col) {
                            hit = true;
                            boards[currentPlayer][row][col] = 'X';
                            cout << "Hit!" << endl;
                            break;
                        }
                    }
                }
            }

            if (!hit) {
                boards[currentPlayer][row][col] = '*';
                cout << "Miss!" << endl;
            }

            printBoard(currentPlayer);

            bool allShipsSunk = true;
            for (const auto& ship : ships[currentPlayer]) {
                if (boards[currentPlayer][ship.first][ship.second] != 'X') {
                    allShipsSunk = false;
                    break;
                }
            }

            if (allShipsSunk) {
                cout << "Player " << currentPlayer + 1 << " wins! All the opponent's battleships are sunk!" << endl;
                break;
            }

            currentPlayer = (currentPlayer + 1) % NUM_PLAYERS;
        }
    }
};

int main() {
    BattleshipGame game;
    game.playGame();

    return 0;
}

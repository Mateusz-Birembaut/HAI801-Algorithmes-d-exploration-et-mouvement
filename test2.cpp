#include <iostream>
#include <limits>
#include <cstdlib>

using namespace std;

const int PLAYER_X = -1; // AI playing 'X'
const int PLAYER_O = 1;  // AI playing 'O'

char board[3][3] = {{' ', ' ', ' '}, {' ', ' ', ' '}, {' ', ' ', ' '}};

// Function to check if moves are left
bool isMovesLeft() {
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            if (board[i][j] == ' ')
                return true;
    return false;
}

// Evaluate the board
int evaluate() {
    for (int row = 0; row < 3; row++)
        if (board[row][0] == board[row][1] && board[row][1] == board[row][2]) {
            if (board[row][0] == 'O') return +10;
            if (board[row][0] == 'X') return -10;
        }

    for (int col = 0; col < 3; col++)
        if (board[0][col] == board[1][col] && board[1][col] == board[2][col]) {
            if (board[0][col] == 'O') return +10;
            if (board[0][col] == 'X') return -10;
        }

    if (board[0][0] == board[1][1] && board[1][1] == board[2][2]) {
        if (board[0][0] == 'O') return +10;
        if (board[0][0] == 'X') return -10;
    }
    if (board[0][2] == board[1][1] && board[1][1] == board[2][0]) {
        if (board[0][2] == 'O') return +10;
        if (board[0][2] == 'X') return -10;
    }

    return 0; // No winner
}

// Minimax function
int minimax(int depth, bool isMax) {
    int score = evaluate();

    if (score == 10 || score == -10) return score;
    if (!isMovesLeft()) return 0;

    int best = isMax ? -1000 : 1000;

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (board[i][j] == ' ') {
                board[i][j] = isMax ? 'O' : 'X';

                best = isMax ? max(best, minimax(depth + 1, !isMax))
                             : min(best, minimax(depth + 1, !isMax));

                board[i][j] = ' ';
            }
        }
    }
    return best;
}

// Find the best move for a given AI player
pair<int, int> findBestMove(char aiPlayer) {
    int bestVal = (aiPlayer == 'O') ? -1000 : 1000;
    pair<int, int> bestMove = {-1, -1};

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (board[i][j] == ' ') {
                board[i][j] = aiPlayer;
                int moveVal = minimax(0, (aiPlayer == 'O'));
                board[i][j] = ' ';

                if ((aiPlayer == 'O' && moveVal > bestVal) || 
                    (aiPlayer == 'X' && moveVal < bestVal)) {
                    bestMove = {i, j};
                    bestVal = moveVal;
                }
            }
        }
    }
    return bestMove;
}

// Print the board
void printBoard() {
    cout << "-------------\n";
    for (int i = 0; i < 3; i++) {
        cout << "| ";
        for (int j = 0; j < 3; j++) {
            cout << board[i][j] << " | ";
        }
        cout << "\n-------------\n";
    }
}

// AI vs AI match
int main() {
    char currentAI = 'X'; // 'X' starts first

    while (true) {
        printBoard();

        // Find the best move for the current AI
        pair<int, int> bestMove = findBestMove(currentAI);
        if (bestMove.first == -1) {
            cout << "It's a draw!\n";
            break;
        }

        // Apply the move
        board[bestMove.first][bestMove.second] = currentAI;

        // Check for win condition
        int score = evaluate();
        if (score == 10) {
            printBoard();
            cout << "AI playing 'O' wins!\n";
            break;
        } else if (score == -10) {
            printBoard();
            cout << "AI playing 'X' wins!\n";
            break;
        } else if (!isMovesLeft()) {
            printBoard();
            cout << "It's a draw!\n";
            break;
        }

        // Swap AI turns
        currentAI = (currentAI == 'X') ? 'O' : 'X';
    }
    return 0;
}

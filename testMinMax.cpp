#include <iostream>
#include <limits>

using namespace std;

const int PLAYER = -1; // Human
const int AI = 1;      // Computer

char board[3][3] = {{' ', ' ', ' '}, {' ', ' ', ' '}, {' ', ' ', ' '}};

// Function to check if a move is available
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

// Minimax algorithm
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

// Find the best move for AI
pair<int, int> findBestMove() {
    int bestVal = -1000;
    pair<int, int> bestMove = {-1, -1};

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (board[i][j] == ' ') {
                board[i][j] = 'O';
                int moveVal = minimax(0, false);
                board[i][j] = ' ';

                if (moveVal > bestVal) {
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

// Main function
int main() {
    int x, y;
    while (true) {
        printBoard();

        // Player move
        cout << "Enter row and column (0-2): ";
        cin >> x >> y;
        if (board[x][y] != ' ') {
            cout << "Invalid move! Try again.\n";
            continue;
        }
        board[x][y] = 'X';

        if (evaluate() == -10) {
            printBoard();
            cout << "You win!\n";
            break;
        }
        if (!isMovesLeft()) {
            printBoard();
            cout << "It's a draw!\n";
            break;
        }

        // AI move
        pair<int, int> bestMove = findBestMove();
        board[bestMove.first][bestMove.second] = 'O';

        if (evaluate() == 10) {
            printBoard();
            cout << "AI wins!\n";
            break;
        }
        if (!isMovesLeft()) {
            printBoard();
            cout << "It's a draw!\n";
            break;
        }
    }
    return 0;
}

#include "TicTacToe.h"
#include <random>

TicTacToeN::TicTacToeN(int n) : m_n(n) {
    m_separator = "";
    for (int k = 0; k < m_n; k++) {
        m_separator += "----";
    }
    m_separator += "\n";
}


State TicTacToeN::getInitialState() const {
    State s;
    s.board.resize(m_n * m_n, -1); // toutes les cases vides
    s.currentPlayer = 0;           // Joueur 0 commence (par ex. "X")

    return s;
}

 void TicTacToeN::printState(const State& state) const {
    for (int i = 0; i < m_n; i++) {
        std::cout << "| ";
        for (int j = 0; j < m_n; j++) {
            int cell = state.board[i * m_n + j];
            if (cell == -1) {
                std::cout << "." << " | ";
            } else {
                std::cout << (cell == 0 ? "X" : "O") << " | ";
            }
        }
        std::cout << "\n";
        // Utiliser le séparateur pré-calculé
        std::cout << m_separator;
    }
    std::cout << std::endl;
}


bool TicTacToeN::isTerminal(const State& state) const {
    // 1) On vérifie s'il y a un gagnant
    int winner = checkWinner(state);
    if (winner != -1) {
        return true; // quelqu'un a gagné
    }
    // 2) Vérifier si toutes les cases sont remplies => match nul => terminal
    for (int cell : state.board) {
        if (cell == -1) {
            return false; // il reste un coup possible
        }
    }
    return true; // plus de coups, partie nulle
}

double TicTacToeN::getUtility(const State& state, PlayerId player) const {
    int winner = checkWinner(state);
    if (winner == player) {
        return 1.0;
    } else if (winner != -1 && winner != player) {
        return -1.0;
    }
    return 0.0; // nul ou pas encore décidé
}

void TicTacToeN::getResult(State& state, const Agent& agent1, const Agent& agent2) {
    double u1 = getUtility(state, agent1.getPlayerId());
    double u2 = getUtility(state, agent2.getPlayerId());

    if (u1 == 1.0) {
        std::cout << "Joueur 1 gagne !\n";
    } else if (u2 == 1.0) {
        std::cout << "Joueur 2 gagne !\n";
    } else {
        std::cout << "Match nul !\n";
    }
}

std::vector<Action> TicTacToeN::getLegalActions(const State& state) const {
    std::vector<Action> actions;
    int totalCells = m_n * m_n;
    actions.reserve(totalCells);

    for (int i = 0; i < totalCells; i++) {
        if (state.board[i] == -1) {
            Action a;
            a.index = i;
            actions.push_back(a);
        }
    }
    return actions;
}

State TicTacToeN::applyAction(const State& state, const Action& action) const {
    State newState = state;
    newState.board[action.index] = state.currentPlayer;
    // alterne 0 <-> 1 pour l'exemple (s'il n'y a que 2 joueurs)
    newState.currentPlayer = 1 - state.currentPlayer;
    return newState;
}

PlayerId TicTacToeN::getCurrentPlayer(const State& state) const {
    return state.currentPlayer;
}

int TicTacToeN::checkWinner(const State& state) const {
    // Number of marks needed in a row to win
    int neededInARow = m_n;

    // Possible directions: right, down, down-right, down-left
    static const std::vector<std::pair<int,int>> directions = {
        {0, 1}, {1, 0}, {1, 1}, {1, -1}
    };

    for (int row = 0; row < m_n; row++) {
        for (int col = 0; col < m_n; col++) {
            int player = state.board[row * m_n + col];
            if (player == -1) continue;

            // For each direction, check neededInARow in a row
            for (auto [dr, dc] : directions) {
                // End positions
                int endRow = row + (neededInARow - 1) * dr;
                int endCol = col + (neededInARow - 1) * dc;

                // Make sure we stay within the board
                if (endRow < 0 || endRow >= m_n || endCol < 0 || endCol >= m_n)
                    continue;

                bool win = true;
                for (int k = 1; k < neededInARow; k++) {
                    int r = row + k * dr;
                    int c = col + k * dc;
                    if (state.board[r * m_n + c] != player) {
                        win = false;
                        break;
                    }
                }
                if (win) {
                    return player;
                }
            }
        }
    }
    return -1;
}
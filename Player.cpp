#include "Player.h"


Player::Player(PlayerId player) 
    : Agent(player), rng(std::random_device{}()) {
}

Action Player::chooseAction(const Game& game, const State& state) {
    int n = static_cast<int>(std::sqrt(state.board.size()));
    int row, col;
    Action action;

    while (true) {
        std::cout << "Entrez la ligne (0 - " << n - 1 << "): ";
        std::cin >> row;
        std::cout << "Entrez la colonne (0 - " << n - 1 << "): ";
        std::cin >> col;
        
        int index = row * n + col;
        if (index >= 0 && index < state.board.size() && state.board[index] == -1) {
            action.index = index;
            break;
        }
        std::cout << "Case invalide ou déja prise. Veuillez réessayer.\n";
    }

    return action;
}

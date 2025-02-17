#include <memory>
#include "Structs.h"
#include "Agent.h"
#include "Game.h"
#include "MinMaxAgent.h"
#include "AlphaBetaAgent.h"
#include "Player.h"
#include "TicTacToe.h"
#include <chrono>
#include <thread>

void playMatch(Game& game, Agent& agent1, Agent& agent2) {
    State state = game.getInitialState();

    std::cout << "Début du jeu :\n";
    game.printState(state);

    while (!game.isTerminal(state)) { // tant que la partie n'est pas terminée
        PlayerId current = game.getCurrentPlayer(state);
        Action a;

        // pour chaque joueur, on choisit une action
        if (current == agent1.getPlayerId()) {
            a = agent1.chooseAction(game, state);
            std::cout << "Joueur X choisit l'action : " << a.index << std::endl;
        } else {
            a = agent2.chooseAction(game, state);
            std::cout << "Joueur O choisit l'action : " << a.index << std::endl;
        }

        // fait l'action choisie
        state = game.applyAction(state, a);

        // on affiche l'état du jeu
        game.printState(state);

        // on attend un peu
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    }

    // affiche le résultat
    game.getResult(state, agent1, agent2);
}

int main() {
    // creation du jeu de taille nxn
    size_t n = 3;

    TicTacToeN game(n);

    // creation des deux agents
    AlphaBetaAgent joueur1(0);  // = X
    AlphaBetaAgent joueur2(1);  // = O

    playMatch(game, joueur1, joueur2);

    return 0;
}
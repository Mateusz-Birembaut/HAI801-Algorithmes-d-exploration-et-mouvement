#ifndef TICTACTOEN_H
#define TICTACTOEN_H

#include "Game.h"
#include "Structs.h"
#include "Agent.h"
#include <vector>

class TicTacToeN : public Game {
private:
    int m_n; // taille de la grille n×n
    std::string m_separator; // séparateur dynamique

public:
    // Constructeur : on passe la dimension n
    TicTacToeN(int n);

    int getN() { return m_n; }

    // Retourne l'état initial
    State getInitialState() const override;

    void printState(const State &state) const;

    // Indique si la partie est terminée
    bool isTerminal(const State& state) const override;

    // Score pour un joueur donné : +1 si gagnant, -1 si perdant, 0 si nul
    double getUtility(const State& state, PlayerId player) const override;

    void getResult(State& state, const Agent& agent1, const Agent& agent2);

    // Liste des coups possibles : toutes les cases vides
    std::vector<Action> getLegalActions(const State& state) const override;

    // On applique l'action : on place le pion du joueur courant dans la case "action.index"
    State applyAction(const State& state, const Action& action) const override;

    // Joueur dont c'est le tour
    PlayerId getCurrentPlayer(const State& state) const override;

private:
    // Vérifie s'il y a un gagnant ; retourne -1 si pas de gagnant
    int checkWinner(const State& state) const;
};

#endif // TICTACTOEN_H
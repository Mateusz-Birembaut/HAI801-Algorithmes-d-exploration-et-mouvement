#ifndef ALPHABETAAGENT_H
#define ALPHABETAAGENT_H

#include "Agent.h"
#include "Game.h"
#include "Structs.h"
#include <random>

class AlphaBetaAgent : public Agent {
public:
    AlphaBetaAgent(PlayerId player);

    Action chooseAction(const Game& game, const State& state) override;

private:

    std::mt19937 rng;

    std::pair<double, Action> minimax(const Game &game, const State &state, double alpha, double beta, bool maximizingPlayer, int &count);
    std::pair<double, Action> minimax(const Game &game, const State &state, double alpha, double beta, bool maximizingPlayer);
};

#endif // ALPHABETAAGENT_H
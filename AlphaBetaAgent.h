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

    double alphaBetaMax(const Game& game, const State& state, double alpha, double beta);
    double alphaBetaMin(const Game& game, const State& state, double alpha, double beta);
};

#endif // ALPHABETAAGENT_H
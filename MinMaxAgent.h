#ifndef MINMAXAGENT_H
#define MINMAXAGENT_H

#include "Structs.h"
#include "Agent.h"
#include "Game.h"
#include <random>

class MinMaxAgent : public Agent {
public:
    // Constructeur
    MinMaxAgent(PlayerId player);

    Action chooseAction(const Game& game, const State& state) override;

private:
    std::mt19937 rng;

    std::pair<double, Action> minimax(const Game &game, const State &state, bool maximizingPlayer, int &count);
    std::pair<double, Action> minimax(const Game &game, const State &state, bool maximizingPlayer);
};

#endif // MINMAXAGENT_H
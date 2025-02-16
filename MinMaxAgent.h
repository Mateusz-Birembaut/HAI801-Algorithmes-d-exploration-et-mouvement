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

    // Choix d'action selon Min-Max (version simplifiée)
    Action chooseAction(const Game& game, const State& state) override;

private:
    std::mt19937 rng;
    
    // Partie MAX
    double maxValue(const Game& game, const State& state);

    // Partie MIN
    double minValue(const Game& game, const State& state);
};

#endif // MINMAXAGENT_H
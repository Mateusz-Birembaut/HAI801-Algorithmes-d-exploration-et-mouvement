#ifndef PLAYER_H
#define PLAYER_H

#include "Structs.h"
#include "Agent.h"
#include "Game.h"
#include <random>

class Player : public Agent {
public:
    // Constructeur
    Player(PlayerId player);

    Action chooseAction(const Game& game, const State& state) override;

private:
    std::mt19937 rng;
};

#endif // PLAYER_H
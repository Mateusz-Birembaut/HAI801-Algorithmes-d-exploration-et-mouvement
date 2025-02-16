#ifndef GAME_H
#define GAME_H

#include "Structs.h"
#include "Agent.h"
#include <vector>

class Agent;

class Game {
public:
    virtual ~Game() = default;

    virtual State getInitialState() const = 0;
    virtual bool isTerminal(const State& state) const = 0;
    virtual double getUtility(const State& state, PlayerId player) const = 0;
    virtual std::vector<Action> getLegalActions(const State& state) const = 0;
    virtual State applyAction(const State& state, const Action& action) const = 0;
    virtual PlayerId getCurrentPlayer(const State& state) const = 0;
    virtual void printState(const State& state) const = 0;
    virtual void getResult(State& state, const Agent& agent1, const Agent& agent2) = 0;
};

#endif // GAME_H
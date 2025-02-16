#include "MinMaxAgent.h"

MinMaxAgent::MinMaxAgent(PlayerId player) 
    : Agent(player), rng(std::random_device{}()) {
}

Action MinMaxAgent::chooseAction(const Game& game, const State& state) {
    double bestValue = NEG_INF;
    std::vector<Action> bestActions;

    // Récupère toutes les actions légales
    auto actions = game.getLegalActions(state);


    for (const auto& action : actions) {
        // On simule l'action
        State nextState = game.applyAction(state, action);
        // Comme on est "max" (notre joueur),
        // on regarde la valeur de l'état suivant en mode "min"
        double value = minValue(game, nextState);

        if (value == bestValue) {
            bestActions.push_back(action);
        } else if (value > bestValue) {
            bestValue = value;
            bestActions.clear();
            bestActions.push_back(action);
        }
    }

    // On choisit une action aléatoire parmi les meilleures
    std::uniform_int_distribution<size_t> dist(0, bestActions.size() - 1);
    Action bestAction = bestActions[dist(rng)];

    return bestAction;
}

double MinMaxAgent::maxValue(const Game& game, const State& state) {
    if (game.isTerminal(state)) {
        return game.getUtility(state, this->m_player);
    }
    double value = NEG_INF;
    auto actions = game.getLegalActions(state);
    for (const auto& action : actions) {
        State nextState = game.applyAction(state, action);
        value = std::max(value, minValue(game, nextState));
    }
    return value;
}

double MinMaxAgent::minValue(const Game& game, const State& state) {
    if (game.isTerminal(state)) {
        return game.getUtility(state, this->m_player);
    }
    double value = POS_INF;
    auto actions = game.getLegalActions(state);
    for (const auto& action : actions) {
        State nextState = game.applyAction(state, action);
        value = std::min(value, maxValue(game, nextState));
    }
    return value;
}
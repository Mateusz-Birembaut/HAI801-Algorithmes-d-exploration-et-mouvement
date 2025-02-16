#include "AlphaBetaAgent.h"

AlphaBetaAgent::AlphaBetaAgent(PlayerId player) 
    : Agent(player), rng(std::random_device{}()) {
}

Action AlphaBetaAgent::chooseAction(const Game& game, const State& state) {
    double bestValue = NEG_INF;
    std::vector<Action> bestActions;

    double alpha = NEG_INF;
    double beta = POS_INF;

    // Récupère toutes les actions légales
    auto actions = game.getLegalActions(state);


    for (const auto& action : actions) {
        // On simule l'action
        State nextState = game.applyAction(state, action);
        // Comme on est "max" (notre joueur),
        // on regarde la valeur de l'état suivant en mode "min"
        double value = alphaBetaMin(game, nextState, alpha, beta);

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

double AlphaBetaAgent::alphaBetaMax(const Game& game, const State& state, double alpha, double beta) {
    if (game.isTerminal(state)) {
        return game.getUtility(state, this->m_player);
    }
    double value = NEG_INF;
    auto actions = game.getLegalActions(state);
    
    for (const auto& action : actions) {
        State nextState = game.applyAction(state, action);
        value = std::max(value, alphaBetaMin(game, nextState, alpha, beta));
        alpha = std::max(alpha, value);
        if (alpha >= beta) {
            // Coupure : inutile d'explorer les autres actions
            break;
        }
    }
    return value;
}

double AlphaBetaAgent::alphaBetaMin(const Game& game, const State& state, double alpha, double beta) {
    if (game.isTerminal(state)) {
        return game.getUtility(state, this->m_player);
    }
    double value = POS_INF;
    auto actions = game.getLegalActions(state);
    
    for (const auto& action : actions) {
        State nextState = game.applyAction(state, action);
        value = std::min(value, alphaBetaMax(game, nextState, alpha, beta));
        beta = std::min(beta, value);
        if (alpha >= beta) {
            // Coupure : inutile d'explorer les autres actions
            break;
        }
    }
    return value;
}
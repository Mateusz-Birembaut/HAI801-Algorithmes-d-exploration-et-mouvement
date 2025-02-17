#include "AlphaBetaAgent.h"

AlphaBetaAgent::AlphaBetaAgent(PlayerId player) 
    : Agent(player), rng(std::random_device{}()) {
}

Action AlphaBetaAgent::chooseAction(const Game& game, const State& state) {
    double alpha = -INFINITY;
    double beta = INFINITY;
    int count = 0;
    Action action = minimax(game, state, alpha, beta, true, count).second;
    std::cout << "Nombre de noeuds explorés : " << count << std::endl;
    return action;
} 

std::pair<double, Action> AlphaBetaAgent::minimax(const Game& game, const State& state, double alpha, double beta, bool maximizingPlayer, int & count) {
    if (game.isTerminal(state)) {
        return {game.getUtility(state, this->m_player), Action()};
    }
    double bestValue;
    Action bestAction;

    if (maximizingPlayer) {
        bestValue = NEG_INF;
        auto actions = game.getLegalActions(state);
        std::shuffle(actions.begin(), actions.end(), rng);
        for (const auto& action : actions) {
            State nextState = game.applyAction(state, action);
            double value = minimax(game, nextState, alpha, beta, false, count).first;
            count++;
            if (value > bestValue) {
                bestValue = value;
                bestAction = action;
            }
            alpha = std::max(alpha, value);
            if (beta <= alpha) {
                break;
            }
        }
    } else {
        bestValue = POS_INF;
        auto actions = game.getLegalActions(state);
        shuffle(actions.begin(), actions.end(), rng);
        for (const auto& action : actions) {
            State nextState = game.applyAction(state, action);
            double value = minimax(game, nextState, alpha, beta, true, count).first;
            count++;
            if (value < bestValue) {
                bestValue = value;
                bestAction = action;
            }
            beta = std::min(beta, value);
            if (beta <= alpha) {
                break;
            }
        }
    }
    return {bestValue, bestAction};
}
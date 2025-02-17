#include "MinMaxAgent.h"

MinMaxAgent::MinMaxAgent(PlayerId player) 
    : Agent(player), rng(std::random_device{}()) {
}

Action MinMaxAgent::chooseAction(const Game& game, const State& state) {
    int count = 0;
    Action action = minimax(game, state, true, count).second;
    std::cout << "Nombre de noeuds explorés : " << count << std::endl;
    return action;
}

std::pair<double, Action> MinMaxAgent::minimax(const Game& game, const State& state, bool maximizingPlayer, int & count) {
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
            double value = minimax(game, nextState, false, count).first;
            count++;
            if (value > bestValue) {
                bestValue = value;
                bestAction = action;
            }

        }
    } else {
        bestValue = POS_INF;
        auto actions = game.getLegalActions(state);
        std::shuffle(actions.begin(), actions.end(), rng);
        for (const auto& action : actions) {
            State nextState = game.applyAction(state, action);
            double value = minimax(game, nextState, true, count).first;
            count++;
            if (value < bestValue) {
                bestValue = value;
                bestAction = action;
            }
        }

    }
    return {bestValue, bestAction};

}

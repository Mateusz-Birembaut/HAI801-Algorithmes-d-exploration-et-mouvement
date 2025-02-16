#ifndef AGENT_H
#define AGENT_H

#include "Structs.h"
#include "Game.h"

class Game;


class Agent {
protected:
    PlayerId m_player;  // Identifiant du joueur (ex: 0 pour X, 1 pour O)

public:
    Agent(PlayerId player);
    virtual ~Agent() = default;

    // Méthode principale : choisir une action pour 'state' dans le 'game'
    virtual Action chooseAction(const Game& game, const State& state) = 0;

    // Accès au PlayerId
    PlayerId getPlayerId() const;
};

#endif // AGENT_H
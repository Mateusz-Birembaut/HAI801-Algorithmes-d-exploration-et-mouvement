#include "Agent.h"

Agent::Agent(PlayerId player) : m_player(player) {}

PlayerId Agent::getPlayerId() const {
    return m_player;
}
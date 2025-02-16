#ifndef STRUCTS_H
#define STRUCTS_H


#include <vector>
#include <limits>
#include <iostream>
#include <algorithm>


using PlayerId = int;

struct Action {
    int index; // Dans un plateau n×n, l'index varie de 0 à n*n - 1
};

struct State {
    // Un plateau n×n sera stocké dans un vector de taille n*n
    // Par convention, -1 = case vide, sinon 0,1,... pour identifier le joueur
    std::vector<int> board;

    // Joueur courant
    PlayerId currentPlayer;
};

// Constantes
constexpr double NEG_INF = -std::numeric_limits<double>::infinity();
constexpr double POS_INF =  std::numeric_limits<double>::infinity();

#endif // STRUCTS_H
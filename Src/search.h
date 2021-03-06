// search.h
// Aswin van Woudenberg

#include <utility>
#include <functional>

#include "move.h"
#include "state.h"
#include "node.h"

#ifndef SEARCH_H
#define SEARCH_H

using MoveEval = std::pair<Move,int>;

MoveEval alphaBeta(const State &board, int ply, std::function<int(State &state, Player p)> eval);
MoveEval alphaBeta(State &board, int ply, Player player, Player opponent, int alpha, int beta, std::function<int(State &state, Player p)> eval);
MoveEval UCTSearch(const State &board, int ply, std::function<int(State &state, Player p)> eval);
Node* UCTSelect(Node &n);
void PlaySimulation(Node &n, std::function<int(State &state, Player p)> eval);
#endif // SEARCH_H

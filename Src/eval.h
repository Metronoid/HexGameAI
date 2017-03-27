// eval.h
// Aswin van Woudenberg

#include "state.h"

#ifndef EVAL_H
#define EVAL_H

int getMonteCarloEval(const State &board, Player player, int trials);
int getRandomEval(const State &board, Player);

#endif // EVAL_H


// eval.cpp
// Aswin van Woudenberg

#include "eval.h"
#include "move.h"

#include <tuple>
#include <limits>
#include <algorithm>

int getMonteCarloEval(const State &board, Player player, int trials)
{
    std::vector<Move> moves = board.getMoves();

    int wins = 0;

    for (int i = 0; i < trials; ++i)
    {
        State mcBoard = board;

        std::random_shuffle(moves.begin(), moves.end());
        for (const Move &m: moves) 
            mcBoard.doMove(m);        
        if (mcBoard.getWinner() == player) 
            wins++;
    }
    //std::cout << wins - trials / 2 << std::endl;
    wins = wins - trials / 2;
    if(wins == 0){
        wins = -1;
    }
    return wins;
}

int getRandomEval(const State &board, Player)
{
    return rand() % 101 - 50;
}


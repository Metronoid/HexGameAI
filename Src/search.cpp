// search.cpp
// Aswin van Woudenberg

#include <vector>
#include <limits>

#include "search.h"
#include "eval.h"

Move alphaBeta(const State &b, int ply, std::function<int(State &state, Player p)> eval)
{
    State board(b);
    Player player = board.getPlayer();
    Player opponent = board.getOpponent(); 

    return alphaBeta(board, ply, player, opponent, std::numeric_limits<int>::min() + 1, std::numeric_limits<int>::max(), eval).first;
}

MoveEval alphaBeta(State &board, int ply, Player player, Player opponent, int alpha, int beta, std::function<int(State &state, Player p)> eval)
{
    if (ply == 0)
        return std::make_pair(Move(), eval(board, player));

    std::vector<Move> moves = board.getRelevantMoves();
    if (moves.size() == 0)
        return std::make_pair(Move(), eval(board, player));

    MoveEval best = std::make_pair(Move(),alpha);
    for (Move &move: moves) {
        board.doMove(move);
        MoveEval me = alphaBeta(board, ply - 1, opponent, player, -beta, -alpha, eval);
        board.undoMove(move);

        if (-me.second > alpha) {
            alpha = -me.second;
            best = std::make_pair(move,alpha);
        }
        if (alpha >= beta) 
            return best;
    }
    return best;
}


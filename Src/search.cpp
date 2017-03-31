// search.cpp
// Aswin van Woudenberg

#include <vector>
#include <limits>
#include <math.h> 

#include "search.h"
#include "eval.h"
#include "node.h"


MoveEval alphaBeta(const State &b, int ply, std::function<int(State &state, Player p)> eval)
{
    State board(b);
    Player player = board.getPlayer();
    Player opponent = board.getOpponent(); 

    return alphaBeta(board, ply, player, opponent, std::numeric_limits<int>::min() + 1, std::numeric_limits<int>::max(), eval);
}

MoveEval alphaBeta(State &board, int ply, Player player, Player opponent, int alpha, int beta, std::function<int(State &state, Player p)> eval)
{
    if (ply == 0)
        return std::make_pair(Move(), eval(board, player));

    std::vector<Move> moves = board.getMoves();
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
        //std::cout << alpha << std::endl;
        if (alpha >= beta) 
            return best;
    }
    return best;
}

void PlaySimulation(State &board, Node n, std::function<int(State &state, Player p)> eval)
{
    int randomResult = 0;
    int visits = n.getVisits();
    Node* child = n.getChild();
    if(visits == 0){
        randomResult = eval(board, board.getPlayer());
    }else{
        if(child == nullptr){
            n.createChildren();
        }

        Node next = UCTSelect(n);

        board.doMove(next.getMove());
        PlaySimulation(board, next, eval);
        board.undoMove(next.getMove());
    }

    n.setVisits(visits+=1);
    n.updateWin(randomresult);
    //if (&child != nullptr)
    //    SetBest(n);
}


MoveEval UCTSearch(const State &b, int ply, std::function<int(State &state, Player p)> eval)
{
    // When doing a tree search we need to start from somewhere, the root.
    int nSimulations = 0;
    State board(b);
    Node root(board);

    // We might have an horizon effect going on by limiting the max simulations.
    // TODO: Create a timer for how long simulations may last.
    while(nSimulations < ply){
        PlaySimulation(board,root,eval);
        nSimulations++;
    }

    Node* test = root.getBest();
    std::cout << test << '\n';

    //Node best = *(root.getBest());

    // Crashes when best is a nullptr
    //return std::make_pair(best.getMove(),best.getScore());

}

Node UCTSelect(Node n)
{
    // Larger values give uniform search
    // Smaller values give very selective search
    /*const int UCTK = 1;

    int bestUCT = 0;
    int winrate = 0;
    int uct = 0;
    int uctValue = 0;

    Node result;
    Node* next = n.getChild();
    while(next != nullptr){
        if(&next.getVisits() > 0){
           winrate = next.getWins()/next.getVisits(); 
           uct = UCTK*sqrt(n.getVisits()/(5*next.getVisits()));
           uctValue = winrate + uct;
        }else{
           uctValue = 10000 + rand() * 1000;
        }

        if(uctValue > bestUCT){
            bestUCT = uctValue;
            result = next;
        }

        next = next.getSibbling();
    }
    return result;*/
}


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

void PlaySimulation(State &board, Node &n, std::function<int(State &state, Player p)> eval)
{
    int randomResult = 0;
    int visits = n.getVisits();
    Node* child = n.getChild();

    std::cout << "visited: " << visits << '\n';

    if(visits == 0){
        randomResult = eval(board, board.getPlayer());
        //std::cout << randomResult << '\n';
    }else{
        if(child == nullptr){
            n.createChildren();
            child = n.getChild();
        }
        Node next(UCTSelect(n));
        std::cout << next.getMove();
        std::cout << '\n';
        board.doMove(next.getMove());
        PlaySimulation(board, next, eval);
        std::cout << next.getMove();
        std::cout << '\n';
        board.undoMove(next.getMove());
    }

    n.setVisits(visits+=1);
    n.updateWin(randomResult);
    if (child != nullptr){
        n.setBest(*child);
    }
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

    // Crashes when best is a nullptr
    if(root.getBest() == nullptr){
        return std::make_pair(board.getMoves()[0],root.getScore());
    }else{
        Node best(*(root.getBest()));
        return std::make_pair(best.getMove(),best.getScore());
    }

}

Node UCTSelect(Node &n)
{
    // Larger values give uniform search
    // Smaller values give very selective search
    const int UCTK = 1;

    int bestUCT = 0;
    int winrate = 0;
    int uct = 0;
    int uctValue = 0;

    Node* next = n.getChild();
    Node* result = next;
    while(next != nullptr){
        int visits = (*next).getVisits();
        if(visits > 0){
           winrate = (*next).getWins()/visits; 
           uct = UCTK*sqrt(visits/(5*visits));
           uctValue = winrate + uct;
        }else{
           uctValue = 10000 + rand() * 1000;
        }
        
        if(uctValue > bestUCT){
            bestUCT = uctValue;
            result = next;
        }
        
        next = (*next).getSibbling();
    }
    
    Node end(*result);
    return end;
}


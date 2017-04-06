// search.cpp
// Aswin van Woudenberg

#include <vector>
#include <limits>
#include <math.h> 

#include "search.h"
#include "eval.h"
#include "node.h"
#include <cfloat>


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

void PlaySimulation(Node &n, int &rResult, std::function<int(State &state, Player p)> eval)
{
    int visits = n.getVisits();
    Node* child = n.getChild();
    State* board = n.getState();

    //std::cout << "visited: " << visits << '\n';

    if(visits < 1){
        rResult = eval(*board, (*board).getPlayer());
        //std::cout << (*board).getPlayer() << '\n';
        //std::cout << n.getOwner() << '\n';
        //std::cout << (*board).getOpponent() << n.getMove() << '\n';
        //std::cout << rResult << '\n';
    }else{
        //if(n.getDone() == true){
        //    return;
        //}
        if(child == nullptr){
            n.createChildren();
            child = n.getChild();
        }
        Node* selected = UCTSelect(n);
        // TODO: Get rid of recursion.
        if(selected != nullptr)
            PlaySimulation(*selected,rResult, eval);
    }
    n.updateWin(rResult);
    rResult = -rResult;
    n.setVisits(visits+=1);
    if (child != nullptr){
        n.setBest();
        n.calculateDone();
    }
}


MoveEval UCTSearch(const State &b, int ply, std::function<int(State &state, Player p)> eval)
{
    // When doing a tree search we need to start from somewhere, the root.
    int nSimulations = 0;
    int rResult = 0;
    State board(b);
    Node root(&board);
    // TODO: Root should be taken from the existing tree.

    // We might have an horizon effect going on by limiting the max simulations.
    // TODO: Create a timer for how long simulations may last.
    while(nSimulations < ply && !root.getDone()){
        PlaySimulation(root,rResult,eval);
        nSimulations++;
    }
    // Crashes when best is a nullptr
    //if(root.getBest() == nullptr){
        //return std::make_pair(board.getMoves()[0],root.getScore());
    //}else{
        Node* best = root.getBest();
        //std::cout << (*best).getScore() << std::endl;
        return std::make_pair((*best).getMove(),round((*best).getScore()));
    //}

}

Node* UCTSelect(Node &n)
{
    // Larger values give uniform search
    // Smaller values give very selective search
    const float UCTK = 1;

    float bestUCT = 0;
    float winrate = 0;
    float uct = 0;
    float uctValue = 0;

    Node* next = n.getChild();
    Node* result = nullptr;
    while(next != nullptr){
        if(next -> getDone() == false){
            float visits = next -> getVisits() + FLT_EPSILON;
            //if(visits > 0){
                winrate = next -> getScore(); 
                uct = UCTK*sqrt(visits + 1/(visits + FLT_EPSILON));
                uctValue = winrate + uct;
            //    std::cout << uct << '\n';
            //}//else{
                //Always play a random unexplored move first.
               // uctValue = ((float) rand() / (RAND_MAX)) * 10000;
            //}
            
            if(uctValue > bestUCT){
                bestUCT = uctValue;
                result = next;
            }
        }
        next = next -> getSibbling();
           // if((*(*next).getState()).getMoves().size() < 1){}
    }

    return result;
}


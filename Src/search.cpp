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

void PlaySimulation(Node &n, int &rResult, std::function<int(State &state, Player p)> eval)
{
    Node* selected = &n;
    std::vector<Node *> nodes;
    while(selected != nullptr){

    //     //std::cout << "visited: " << visits << '\n';
            nodes.push_back(selected);

        if( selected -> getVisits() < 1){
            State test = *(selected -> getState());
            rResult = eval(test, selected -> getState() -> getPlayer());
            break;
            //std::cout << (*board).getPlayer() << '\n';
            //std::cout << n.getOwner() << '\n';
            //std::cout << (*board).getOpponent() << n.getMove() << '\n';
            //std::cout << rResult << '\n';
        }else{
            if(selected -> getChild() == nullptr){
                selected -> createChildren();
            }
            selected = UCTSelect(*selected);
        }
    }

    for(std::vector<int>::size_type i = nodes.size() - 1; 
    i != (std::vector<int>::size_type) -1; i--) {
        nodes[i] -> updateWin(rResult);
        rResult = -rResult;
        nodes[i] -> setVisits(nodes[i] -> getVisits() + 1);
        if (nodes[i] -> getChild() != nullptr){
            nodes[i] -> setBest();
            nodes[i] -> calculateDone();
        }
    }
}


MoveEval UCTSearch(const State &b, int ply, std::function<int(State &state, Player p)> eval)
{
    // When doing a tree search we need to start from somewhere, the root.
    int nSimulations = 0;
    int rResult = 0;
    Node root(new State(b));
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
        //std::cout << (*best).getScore() << std::endl;
        return std::make_pair(root.getBest() -> getMove(),round(root.getBest() -> getScore()));
    //}

}

Node* UCTSelect(Node &n)
{
    // Larger values give uniform search
    // Smaller values give very selective search
    const float UCTK = 0.5;

    float bestUCT = 0;
    float winrate = 0;
    float uct = 0;
    float uctValue = 0;

    Node* next = n.getChild();
    Node* result = nullptr;
    while(next != nullptr){
        if(next -> getDone() == false){
            if(next -> getVisits() > 0){
                winrate = next -> getScore(); 
                uct = UCTK*sqrt(log(n.getVisits())/(next -> getVisits() * 5));
                uctValue = winrate + uct;
            //    std::cout << uct << '\n';
            }else{
            //Always play a random unexplored move first.
               uctValue = ((float) rand() / (RAND_MAX)) * 10000;
            }
            
            if(uctValue > bestUCT){
                bestUCT = uctValue;
                result = next;
            }
        }
        next = next -> getSibbling();
           // if((*(*next).getState()).getMoves().size() < 1){}
    }
    delete next;
    return result;
}


// search.cpp
// Aswin van Woudenberg

#include <vector>
#include <limits>
#include <math.h> 

#include "search.h"
#include "eval.h"
#include "node.h"

void PlaySimulation(Node &n, int &rResult, std::function<int(State &state, Player p)> eval)
{
    Node* selected = &n;
    std::vector<Node *> nodes;
    while(selected != nullptr){

    //     //std::cout << "visited: " << visits << '\n';
            nodes.push_back(selected);
            if n.visits > 30000{
                
            }

        if( selected -> getVisits() < 1){
            State test = *(selected -> getState());
            //TODO: If we want to build this application for more than 1 evaluation, make it multi threaded.
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
    }
    delete next;
    return result;
}


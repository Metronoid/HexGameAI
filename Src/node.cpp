// node.cpp
// Wander van der Wal

#include <vector>
#include <limits>

#include "node.h"
#include "move.h"
#include "state.h"

Node::Node(const Node &n): wins(n.wins),visits(n.visits),child(n.child),
sibbling(n.sibbling),bestNode(n.bestNode),state(n.state),move(n.move){}

Node::Node(State board, Move action): state(board),move(action){}

Node::Node(State board): state(board),move(std::make_pair(-1,-1)){}

void Node::updateWin(int score){
    if(score >= 1){
        wins++;
    };
}

int Node::getScore(){
    int score = 0;
    if(visits != 0){
        score = wins / visits;
    }
    return score;
}

void Node::createChildren(){
    std::vector<Move> moves = state.getMoves();
    Node newChild(state,moves.back());
    moves.pop_back();

    Node* check = &newChild;
    child = check;

    for (const Move &m: moves) {
        Node newest(state,m);
        (*check).setSibbling(newest);
        check = &newest;
        //std::cout << check.getMove() << std::endl;
    }
}
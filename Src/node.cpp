// node.cpp
// Wander van der Wal

#include <vector>
#include <limits>

#include "node.h"
#include "move.h"
#include "state.h"

Node::Node(State board){
    state = board;
}

void Node::updateWin(int score){
    if(score >= 0){
        wins++;
    };
}

void Node::createChildren(){

}
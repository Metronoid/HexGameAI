// node.cpp
// Wander van der Wal

#include <vector>
#include <limits>

#include "node.h"
#include "move.h"
#include "state.h"

Node::Node(State* board, Move action): state(board),move(action){
    owner = (*board).getPlayer();
    (*board).doMove(action);
    if((*board).getMoves().size() == 0){
        done = true;
        //std::cout << (*board) << '\n';
    }
}

Node::Node(State* board): state(board),move(std::make_pair(-1,-1)){
    owner = (*board).getPlayer();
}

void Node::updateWin(int score){
    if(owner == Player::BLUE){
        if((*state).getPlayer() == Player::RED){
            if(score <= 0){
                wins++;
            };
        }else{
            if(score >= 1){
                wins++;
            };
        }
    }else{
        if((*state).getPlayer() == Player::RED){
            if(score >= 1){
                wins++;
            };
        }else{
            if(score <= 0){
                wins++;
            };
        }
    }
}

double Node::getScore(){
    if(getVisits() != 0){
        return wins / visits;
    }
    return 0;
}

void Node::setBest(){
    Node* next = getChild();
    double highestScore = -1;
    while(next != nullptr){
        if((*next).getScore() > highestScore){
            highestScore = (*next).getScore();
            setBest(next);
        }
        next = (*next).getSibbling();
    }  
}

void Node::calculateDone(){
    Node* next = getChild();
    bool result = true;
    while(next != nullptr){
        if(!(*next).getDone()){
            result = false;
        }
        next = (*next).getSibbling();
    } 
    setDone(result); 
}

// Expansion
void Node::createChildren(){
    std::vector<Move> moves = (*state).getMoves();
    if(moves.size() != 0){
        setChild(new Node(new State(*state),moves.back()));
        moves.pop_back();
        Node* check = getChild();

        for (const Move &m: moves) {
            (*check).setSibbling(new Node(new State(*state),m));
            check = (*check).getSibbling();
            //std::vector<Move> checkMoves = (*nextState).getMoves();
            //std::cout << check.getMove() << std::endl;
        }
    }
}
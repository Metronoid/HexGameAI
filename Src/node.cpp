// node.cpp
// Wander van der Wal

#include <vector>
#include <limits>

#include "node.h"
#include "move.h"
#include "state.h"

Node::Node(State* board, Move action): nodeState(board),move(action){
    owner = board -> getPlayer();
    board -> doMove(action);
    if(board -> getMoves().size() == 0){
        done = true;
        //std::cout << (*board) << '\n';
    }
}

Node::Node(State* board): nodeState(board),move(std::make_pair(-1,-1)){
    owner = board -> getPlayer();
}

void Node::updateWin(int score){
    if(owner == Player::BLUE){
        if(nodeState -> getPlayer() == Player::RED){
            if(score <= 0){
                wins++;
            };
        }else{
            if(score >= 1){
                wins++;
            };
        }
    }else{
        if(nodeState -> getPlayer() == Player::RED){
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

float Node::getScore(){
    if(getVisits() != 0){
        return wins / visits;
    }
    return 0;
}

void Node::setBest(){
    Node* next = getChild();
    double highestScore = -1;
    while(next != nullptr){
        if(next -> getScore() > highestScore){
            highestScore = next -> getScore();
            setBest(next);
        }
        next = next -> getSibbling();
    }  
    delete next;
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
    delete next;
}

// Expansion
void Node::createChildren(){
    std::vector<Move> moves = nodeState -> getMoves();
    if(moves.size() != 0){
        setChild(new Node(new State(nodeState.get()),moves.back()));
        moves.pop_back();
        Node* check = getChild();

        for (const Move &m: moves) {
            (*check).setSibbling(new Node(new State(nodeState.get()),m));
            check = (*check).getSibbling();
            //std::vector<Move> checkMoves = (*nextState).getMoves();
            //std::cout << check.getMove() << std::endl;
        }
    }
}
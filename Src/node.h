// node.h
// Wander van der Wal

#ifndef NODE_H
#define NODE_H

#include <utility>
#include <functional>

#include "move.h"
#include "state.h"

class Node {
public:
    Node(State board);

    void setChild(Node* n){child = n;}
    Node* getChild(){return child;}
    void setSibbling(Node* n){sibbling = n;}
    Node* getSibbling(){return sibbling;}
    void setBest(Node* n){bestNode = n;}
    Node* getBest(){return bestNode;}
    void setMove(Move m){move = m;}
    Move getMove(){return move;}
    void setState(State s){state = s;}
    State getState(){return state;}
    void setVisits(int v){visits = v;}
    int getVisits(){return visits;}
    void setWins(int w){wins = w;}
    int getWins(){return wins;}
    int getScore(){return wins/visits;};

    void createChildren();
protected:
    int wins = 0;
    int visits = 0;
    Node* child = nullptr;
    Node* sibbling = nullptr;
    Node* bestNode = nullptr;
    Move move;
    State state;
};


#endif // NODE_H
// node.h
// Wander van der Wal

#ifndef NODE_H
#define NODE_H

#include <utility>
#include <functional>
#include <vector>

#include "move.h"
#include "state.h"

class Node {
public:
    Node(const Node &n);
    Node(State board);
    Node(State board,Move action);

    void setChild(Node &n){child = &n;}
    Node* getChild() const {return child;}
    void setSibbling(Node &n){sibbling = &n;}
    Node* getSibbling() const {return sibbling;}
    void setBest(Node &n){bestNode = &n;}
    Node* getBest() const {return bestNode;}
    Move getMove() const {return move;}
    State getState() const {return state;}
    void setVisits(int v) {visits = v;}
    int getVisits() const {return visits;}
    void setWins(int w) {wins = w;}
    int getWins() const {return wins;}

    int getScore();
    void createChildren();
    void updateWin(int score);

protected:
    int wins = 0;
    int visits = 0;
    Node* child = nullptr;
    Node* sibbling = nullptr;
    Node* bestNode = nullptr;
    const State state;
    const Move move;
};

#endif // NODE_H
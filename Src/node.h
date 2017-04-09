// node.h
// Wander van der Wal

#ifndef NODE_H
#define NODE_H

#include <utility>
#include <functional>
#include <vector>
#include <memory> 

#include "move.h"
#include "state.h"

class Node {
public:
    Node(const Node &n);
    Node(State* board);
    Node(State* board,Move action);

    void setChild(Node* n){child = n;}
    Node* getChild() const {return child;}
    //void setSibbling(std::unique_ptr<Node>n){sibbling = std::move(n);}
    void setSibbling(Node* n){sibbling = n;}
    Node* getSibbling() const {return sibbling;}
    void setBest(Node* n){bestNode = n;}
    void setBest();
    Node* getBest() const {return bestNode;}
    Move getMove() const {return move;}
    State* getState() const {return nodeState.get();}
    void setVisits(float v) {visits = v;}
    float getVisits() const {return visits;}
    void setWins(float w) {wins = w;}
    float getWins() const {return wins;}
    void setOwner(Player p) {owner = p;}
    Player getOwner() const {return owner;}
    void setDone(bool d) {done = d;}
    bool getDone() const {return done;}
    

    float getScore();
    void createChildren();
    void updateWin(int score);
    void calculateDone();


protected:
    float wins = 0;
    float visits = 0;
    Node* child = nullptr;
    Node* sibbling = nullptr;
    Node* bestNode;
    std::unique_ptr<State> nodeState;
    const Move move;
    Player owner;
    bool done = false;
};

#endif // NODE_H
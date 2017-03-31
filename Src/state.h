// state.h
// Aswin van Woudenberg

#ifndef STATE_H
#define STATE_H

#include <ostream>
#include <vector>

#include "hexgraph.h"

using Move = std::pair<int,int>;

enum class Player { NONE, RED, BLUE };

class State {
public:
    State(int size = 11, Player firstPlayer = Player::RED);
    State(const State &board);
    int getSize() const { return size; }
    void clear(int size = 11, Player firstPlayer = Player::RED);
    void doMove(const Move &move);
    void undoMove(const Move &move);
    bool isValidHexagon(int row, int col) const; 
    Player getHexagon(int row, int col) const { return hexagons[row * size + col]; }
    Player getPlayer() const { return currentPlayer; }
    Player getOpponent() const { return (currentPlayer == Player::RED ? Player::BLUE : Player::RED); }
    Player getWinner() const;
    bool isGameOver() const;
    std::vector<Move> getMoves() const;
    std::vector<Move> getRelevantMoves() const;
    friend std::ostream &operator<<(std::ostream &os, const State &b);
    friend class HexGraph;
protected:
    int size;
    Player currentPlayer;
    std::vector<Player> hexagons;
};

std::ostream &operator<<(std::ostream &os, const Player &p);
std::ostream &operator<<(std::ostream &os, const State &s);

#endif // STATE_H


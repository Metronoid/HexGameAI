// game.h
// Aswin van Woudenberg

#ifndef GAME_H
#define GAME_H

#include <stack>
#include <cmath>

#include "move.h"
#include "state.h"
#include "search.h"
#include "eval.h"

enum class PlayerType { HUMAN, COMPUTER };

class Game {
public:
    Game(int size = 2, 
        PlayerType red = PlayerType::HUMAN, 
        PlayerType blue = PlayerType::COMPUTER, 
        Player firstPlayer = Player::RED,
        int trials = 1,
        int plies = 2,
        bool pieRuleAllowed = true);
    ~Game();
    void newGame();
    void newGame(int size, Player firstPlayer = Player::RED);
    void doMove(const Move &move);
    void doComputerMove();
    bool canUndo() const { return !moves.empty(); }
    void undoMove();
    bool isGameOver() const { return board.isGameOver(); }
    int getSize() const { return board.getSize(); }
    bool isPieRuleAllowed() const { return pieRuleAllowed; }
    void setPieRuleAllowed(bool allowed) { pieRuleAllowed = allowed; }
    void applyPieRule();
    Player getCurrentPlayer() const { return board.getPlayer(); }
    Player getWinner() const { return board.getWinner(); }
    PlayerType getPlayerType(Player player) const;
    void setPlayerType(Player player, PlayerType type);
    Player getFirstPlayer() const { return firstPlayer; }
    int getTrials() const { return trials; }
    void setTrials(int num) { trials = num; }
    int getPlies() const { return plies; }
    void setPlies(int num) { plies = num; }
    friend std::ostream &operator<<(std::ostream &os, const Game &g);
protected:
    State board;

    PlayerType red;
    PlayerType blue;
    Player firstPlayer;

    int trials;
    int plies;
    bool pieRuleAllowed;
    bool usedPieRule;

    std::stack<Move> moves;
};

std::ostream &operator<<(std::ostream &os, const Game &g);

#endif // GAME_H


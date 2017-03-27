// game.cpp
// Aswin van Woudenberg

#include <iterator>
#include <algorithm>
#include <string>
#include <functional>

#include "game.h"
#include "ansi.h"

Game::Game(int size, PlayerType red, PlayerType blue, Player firstPlayer, 
        int trials, int plies, bool pieRuleAllowed): 
    board(size, firstPlayer), red(red), blue(blue), firstPlayer(firstPlayer), 
    trials(trials), plies(plies), pieRuleAllowed(pieRuleAllowed), usedPieRule(false) 
{
}

Game::~Game() 
{
}

void Game::newGame()
{
    while (!moves.empty())
        moves.pop();
    board.clear(board.getSize(), firstPlayer);
    usedPieRule = false;
}

void Game::newGame(int size, Player firstPlayer)
{
    while (!moves.empty())
        moves.pop();
    board.clear(size, firstPlayer);
    usedPieRule = false;
}

void Game::doMove(const Move &move)
{
    if (isGameOver())
        throw "The game has already ended!";
    board.doMove(move);
    moves.push(move);
}

void Game::doComputerMove()
{
    using namespace std::placeholders;  // for _1, _2, _3...

    if (isGameOver())
        throw "The game has already ended!";
    doMove(alphaBeta(board, plies, std::bind(getMonteCarloEval, _1, _2, trials)));
    //doMove(alphaBeta(board, plies, getRandomEval));
}

void Game::undoMove()
{
    if (moves.empty())
        throw "There are no moves to undo!";
    board.undoMove(moves.top());
    moves.pop();
    if (moves.size() == 0)
        usedPieRule = false;
}

void Game::applyPieRule()
{
    if (!pieRuleAllowed)
        throw "The pie rule is not allowed!";
    if (moves.size() != 1)
        throw "The pie rule is only allowed directly after the first move!";
    if (usedPieRule)
        throw "The pie rule is only allowed once!";
    PlayerType type = red;
    red = blue;
    blue = type;
    usedPieRule = true;
}

PlayerType Game::getPlayerType(Player player) const
{
    return (player == Player::RED ? red : blue);
}

void Game::setPlayerType(Player player, PlayerType type)
{
    if (player == Player::RED) red = type;
    else blue = type;
}

std::ostream &operator<<(std::ostream &os, const PlayerType &t)
{
    if (t == PlayerType::HUMAN) 
        return os << "Human";
    return os << "Computer";
}

std::ostream &operator<<(std::ostream &os, const Game &g)
{
    os << std::string(g.board.getSize() * 3 + log10(g.board.getSize()) * 2 + 13,'-')
       << std::endl << g.board << std::endl
       << std::string(g.board.getSize() * 3 + log10(g.board.getSize()) * 2 + 13,'-') << std::endl;
       if (g.canUndo()) {
           if (g.getCurrentPlayer() == Player::RED)
               os << Color(ColorValue::BLUE) << "Blue" << Color()
                  << " (" << g.blue << ")";
           else
               os << Color(ColorValue::RED) << "Red" << Color()
                  << " (" << g.red << ")";
           os << " just moved " << g.moves.top() << "." << std::endl;
       }
       if (g.isGameOver()) {
           os << "The game is over. ";
           if (g.getWinner() == Player::RED)
               os << Color(ColorValue::RED) << "Red" << Color();
           else
               os << Color(ColorValue::BLUE) << "Blue" << Color();
           os << " (" << g.getPlayerType(g.getWinner()) << ") has won!" << std::endl;
       } else {
           os << "Turn " << g.moves.size() + 1 << ". ";
           if (g.getCurrentPlayer() == Player::RED)
               os << Color(ColorValue::RED) << "Red" << Color()
                  << " (" << g.red << ")";
           else
               os << Color(ColorValue::BLUE) << "Blue" << Color()
                  << " (" << g.blue << ")";
           os << " has to make a move now. " << std::endl;
       }

    return os;
}


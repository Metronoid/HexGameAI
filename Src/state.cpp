// state.cpp
// Aswin van Woudenberg

#include <cmath>
#include <iomanip>
#include <string>
#include <iostream>

#include "state.h"
#include "ansi.h"

State::State(int size, Player firstPlayer): size(size),
    currentPlayer(firstPlayer), hexagons(size * size, Player::NONE)
{ }

State::State(const State &board): size(board.size),
    currentPlayer(board.currentPlayer)
{
    hexagons = board.hexagons;
}

void State::clear(int size, Player firstPlayer)
{
    this->size = size;
    hexagons.assign(size * size, Player::NONE);
    currentPlayer = firstPlayer;
}

void State::doMove(const Move &move)
{
    if (move.first < 0 || move.first >= size || 
        move.second < 0 || move.second >= size)
        throw "Invalid move!";
    if (hexagons[move.first * size + move.second] != Player::NONE)
        throw "Hexagon isn't empty!";
    hexagons[move.first * size + move.second] = currentPlayer;
    currentPlayer = getOpponent();
}

void State::undoMove(const Move &move)
{
    if (move.first < 0 || move.first >= size || 
        move.second < 0 || move.second >= size)
        throw "Invalid move!";
    if (hexagons[move.first * size + move.second] == Player::NONE)
        throw "Hexagon is empty!";
    if (hexagons[move.first * size + move.second] == currentPlayer)
        throw "Hexagon isn't occupied by previous player!";
    hexagons[move.first * size + move.second] = Player::NONE;
    currentPlayer = getOpponent();
}

Player State::getWinner() const 
{
    HexGraph hexGraph(*this);
    int len = hexGraph.findShortestPathLength(size * size + 0, size * size + 1);
    if (len == 0)
        return Player::RED;
    else if (len == -1)
        return Player::BLUE;
    return Player::NONE;
}

bool State::isGameOver() const
{
    return getWinner() != Player::NONE;
}

std::vector<Move> State::getMoves() const
{
    std::vector<Move> moves;
    if (!isGameOver())
        for (int r = 0; r < size; ++r)
            for (int c = 0; c < size; ++c)
                if (getHexagon(r,c) == Player::NONE)
                    moves.push_back(std::make_pair(r,c));
    return moves;
}

bool State::isValidHexagon(int row, int col) const
{ 
    return row >= 0 && row < size && col >= 0 && col < size; 
}

std::vector<Move> State::getRelevantMoves() const
{
    std::vector<Move> moves;
    if (!isGameOver())
        for (int r = 0; r < size; ++r)
            for (int c = 0; c < size; ++c)
                if (getHexagon(r,c) == Player::NONE) {
                    int mid = static_cast<int>(size / 2);
                    if (r == c && c == mid) 
                        moves.push_back(std::make_pair(r,c));
                    else if (isValidHexagon(r,c+1) && (getHexagon(r,c+1) != Player::NONE || (r == c+1 && r == mid))) moves.push_back(std::make_pair(r,c));
                    else if (isValidHexagon(r+1,c) && (getHexagon(r+1,c) != Player::NONE || (r+1 == c && c== mid))) moves.push_back(std::make_pair(r,c));
                    else if (isValidHexagon(r+1,c-1) && (getHexagon(r+1,c-1) != Player::NONE || (r+1 == c-1 && c-1 == mid))) moves.push_back(std::make_pair(r,c));
                    else if (isValidHexagon(r,c-1) && (getHexagon(r,c-1) != Player::NONE || (r == c-1 && r ==mid))) moves.push_back(std::make_pair(r,c));
                    else if (isValidHexagon(r-1,c) && (getHexagon(r-1,c) != Player::NONE || (r-1 == c && c == mid))) moves.push_back(std::make_pair(r,c));
                    else if (isValidHexagon(r-1,c+1) && (getHexagon(r-1,c+1) != Player::NONE || (r-1 == c+1 && c+1 == mid))) moves.push_back(std::make_pair(r,c));
                    else if (isValidHexagon(r,c+2) && (getHexagon(r,c+2) != Player::NONE || (r == c+2 && r == mid))) moves.push_back(std::make_pair(r,c));
                    else if (isValidHexagon(r+1,c+1) && (getHexagon(r+1,c+1) != Player::NONE || (r+1 == c+1 && c+1 == mid))) moves.push_back(std::make_pair(r,c));
                    else if (isValidHexagon(r+2,c) && (getHexagon(r+2,c) != Player::NONE || (r+2 == c && c == mid))) moves.push_back(std::make_pair(r,c));
                    else if (isValidHexagon(r+2,c-1) && (getHexagon(r+2,c-1) != Player::NONE || (r+2 == c-1 && c-1 == mid))) moves.push_back(std::make_pair(r,c));
                    else if (isValidHexagon(r+2,c-2) && (getHexagon(r+2,c-2) != Player::NONE || (r+2 == c-2 && c-2 == mid))) moves.push_back(std::make_pair(r,c));
                    else if (isValidHexagon(r+1,c-2) && (getHexagon(r+1,c-2) != Player::NONE || (r+1 == c-2 && c-2 == mid))) moves.push_back(std::make_pair(r,c));
                    else if (isValidHexagon(r,c-2) && (getHexagon(r,c-2) != Player::NONE || (r == c-2 && r == mid))) moves.push_back(std::make_pair(r,c));
                    else if (isValidHexagon(r-1,c-1) && (getHexagon(r-1,c-1) != Player::NONE || (r-1 == c-1 && c-1 == mid))) moves.push_back(std::make_pair(r,c));
                    else if (isValidHexagon(r-2,c) && (getHexagon(r-2,c) != Player::NONE || (r-2 == c && c == mid))) moves.push_back(std::make_pair(r,c));
                    else if (isValidHexagon(r-2,c+1) && (getHexagon(r-2,c+1) != Player::NONE || (r-2 == c+1 && c+1 == mid))) moves.push_back(std::make_pair(r,c));
                    else if (isValidHexagon(r-2,c+2) && (getHexagon(r-2,c+2) != Player::NONE || (r-2 == c+2 && c+2 == mid))) moves.push_back(std::make_pair(r,c));
                    else if (isValidHexagon(r-1,c+2) && (getHexagon(r-1,c+2) != Player::NONE || (r-1 == c+2 && c+2 == mid))) moves.push_back(std::make_pair(r,c));
                }
    return moves;
}

std::ostream &operator<<(std::ostream &os, const Player &p)
{
    switch (p) {
         case Player::NONE: os << "-"; break;
         case Player::RED: os << Color(ColorValue::RED) << "R" << Color(); break;
         case Player::BLUE: os << Color(ColorValue::BLUE) << "B" << Color(); break;
    }
    return os;
}

std::ostream &operator<<(std::ostream &os, const State &b)
{
    int indent = log10(b.size);
    os << std::string(indent + b.size + 3, ' ') 
       << Player::RED << std::endl
       << std::string(indent + 5, ' ');
    for (int i = 0; i < b.size; ++i) 
        os << ((i < 26) ? ' ': static_cast<char>('A' + i / 26 - 1)) << " ";
    os << std::endl << std::string(indent + 6, ' ');
    for (int i = 0; i < b.size; ++i) 
        os << static_cast<char>('A' + i % 26) << " ";
    os << std::endl;

    for (int r = 0; r < b.size; ++r)
    {
        os << std::string(indent + r + 1, ' ');
        ((r == b.size / 2) ? os << Player::BLUE : os << " ") << " ";
        (((r + 1) < 10) ? os << " ": os << (r + 1) / 10);
        os << (r + 1) % 10 << "  ";
        for (int c = 0; c < b.size; ++c)
        {
            os << b.hexagons[r * b.size + c] << " ";
        }
        os << " " << r + 1 << (((r+1)<10) ? " ": "");
        ((r == b.size / 2) ? os << " " << Player::BLUE : os << "  ") << std::endl;
    }
    os << std::string(indent + b.size + 7, ' ');
    for (int i = 0; i < b.size; ++i) 
        os << ((i < 26) ? static_cast<char>('A' + i % 26): 
                          static_cast<char>('A' + i / 26 - 1)) << " ";
    os << std::endl << std::string(indent + b.size + 8, ' ');
    for (int i = 0; i < b.size; ++i) 
        os << ((i < 26) ? ' ': static_cast<char>('A' + i % 26)) << " ";
    os << std::endl << std::string(indent + b.size * 2 + 8, ' ') << Player::RED;
    
    return os;
}


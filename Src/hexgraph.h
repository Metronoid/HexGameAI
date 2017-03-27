// hexgraph.h
// Aswin van Woudenberg

#ifndef HEXGRAPH_H
#define HEXGRAPH_H

#include <limits>
#include <utility>
#include <vector>
#include <list>

class State;
enum class Player;

class HexGraph {
public:
    HexGraph(const State &board) : board(board) { }
    std::list<int> findShortestPath(int source, int dest) const;
    int findShortestPathLength(int source, int dest) const;
    int size() const;
protected:
    const State &board;
    mutable Player color;
    mutable std::vector<std::pair<int,int>> adjacentHexagons;
    
    typename std::vector<std::pair<int,int>>::const_iterator cbegin(int v) const;
    typename std::vector<std::pair<int,int>>::const_iterator cend() const; 
    
    void computePaths(int source, std::vector<int> &dist, std::vector<int> &pred) const;
};

#endif // HEXGRAPH_H


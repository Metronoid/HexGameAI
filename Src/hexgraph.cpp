// hexgraph.cpp
// Aswin van Woudenberg
 
#include <set>
#include <iostream>

#include "state.h"

typename std::vector<std::pair<int,int>>::const_iterator HexGraph::cbegin(int v) const {
    int size = board.size;

    adjacentHexagons.clear();

    if (v == size * size) {
        color = Player::RED;
        for (int i = 0; i < size; ++i)
            if (board.hexagons[i] == color || board.hexagons[i] == Player::NONE)
                adjacentHexagons.push_back(std::make_pair(i, (board.hexagons[i] == color ? 0 : 1))); 
    } else if (v == size * size + 1) {
        color = Player::RED;
        for (int i = 0; i < size; ++i)
            if (board.hexagons[size * size - size + i] == color || board.hexagons[size * size - size + i] == Player::NONE)
                adjacentHexagons.push_back(std::make_pair(size * size - size + i, (board.hexagons[size * size - size + i] == color ? 0 : 1)));
    } else if (v == size * size + 2) {
        color = Player::BLUE; 
        for (int i = 0; i < size; ++i)
            if (board.hexagons[size * i] == color || board.hexagons[size * i] == Player::NONE)
                adjacentHexagons.push_back(std::make_pair(size * i, (board.hexagons[size * i] == color ? 0 : 1)));
    } else if (v ==  size * size + 3) {
        color = Player::BLUE;
        for (int i = 0; i < size; ++i)
            if (board.hexagons[size * i + size - 1] == color || board.hexagons[size * i + size - 1] == Player::NONE)
                adjacentHexagons.push_back(std::make_pair(size * i + size - 1, (board.hexagons[size * i + size - 1] == color ? 0 : 1)));
    } else if (color == board.hexagons[v]) { 
        if (v - 1 > 0 && v - 1 < size * size && v % size != 0 && (board.hexagons[v - 1] == color || board.hexagons[v - 1] == Player::NONE)) 
            adjacentHexagons.push_back(std::make_pair(v - 1, (board.hexagons[v - 1] == color ? 0 : 1)));
        if (v + 1 > 0 && v + 1 < size * size && (v + 1) % size != 0 && (board.hexagons[v + 1] == color || board.hexagons[v + 1] == Player::NONE)) 
            adjacentHexagons.push_back(std::make_pair(v + 1, (board.hexagons[v + 1] == color ? 0 : 1)));
        if (v + size > 0 && v + size < size * size && (board.hexagons[v + size] == color || board.hexagons[v + size] == Player::NONE)) 
            adjacentHexagons.push_back(std::make_pair(v + size, (board.hexagons[v + size] == color ? 0 : 1)));
        if (v + size - 1 > 0 && v + size - 1 < size * size && v % size != 0 && (board.hexagons[v + size - 1] == color || board.hexagons[v + size - 1] == Player::NONE)) 
            adjacentHexagons.push_back(std::make_pair(v + size - 1, (board.hexagons[v + size - 1] == color ? 0 : 1)));
        if (v - size + 1 > 0 && v - size + 1 < size * size && (v + 1) % size != 0 && (board.hexagons[v - size + 1] == color || board.hexagons[v - size + 1] == Player::NONE)) 
            adjacentHexagons.push_back(std::make_pair(v - size + 1, (board.hexagons[v - size + 1] == color ? 0 : 1)));
        if (v - size > 0 && v - size < size * size && (board.hexagons[v - size] == color || board.hexagons[v - size] == Player::NONE)) 
            adjacentHexagons.push_back(std::make_pair(v - size, (board.hexagons[v - size] == color ? 0 : 1)));
        if (v < size * size && v >= size * (size - 1) && color == Player::RED)
            adjacentHexagons.push_back(std::make_pair(size * size + 1, 0));
        if ((v + 1) % size == 0 && color == Player::BLUE)
            adjacentHexagons.push_back(std::make_pair(size * size + 3, 0));
    } else { // v is not occupied
        if (v - 1 > 0 && v - 1 < size * size && v % size != 0 && (board.hexagons[v - 1] == color || board.hexagons[v - 1] == Player::NONE)) 
            adjacentHexagons.push_back(std::make_pair(v - 1, (board.hexagons[v - 1] == color ? 1 : 2)));
        if (v + 1 > 0 && v + 1 < size * size && (v + 1) % size != 0 && (board.hexagons[v + 1] == color || board.hexagons[v + 1] == Player::NONE)) 
            adjacentHexagons.push_back(std::make_pair(v + 1, (board.hexagons[v + 1] == color ? 1 : 2)));
        if (v + size > 0 && v + size < size * size && (board.hexagons[v + size] == color || board.hexagons[v + size] == Player::NONE)) 
            adjacentHexagons.push_back(std::make_pair(v + size, (board.hexagons[v + size] == color ? 1 : 2)));
        if (v + size - 1 > 0 && v + size - 1 < size * size && v % size != 0 && (board.hexagons[v + size - 1] == color || board.hexagons[v + size - 1] == Player::NONE)) 
            adjacentHexagons.push_back(std::make_pair(v + size - 1, (board.hexagons[v + size - 1] == color ? 1 : 2)));
        if (v - size + 1 > 0 && v - size + 1 < size * size && (v + 1) % size != 0 && (board.hexagons[v - size + 1] == color || board.hexagons[v - size + 1] == Player::NONE)) 
            adjacentHexagons.push_back(std::make_pair(v - size + 1, (board.hexagons[v - size + 1] == color ? 1 : 2)));
        if (v - size > 0 && v - size < size * size && (board.hexagons[v - size] == color || board.hexagons[v - size] == Player::NONE)) 
            adjacentHexagons.push_back(std::make_pair(v - size, (board.hexagons[v - size] == color ? 1 : 2)));
        if (v < size * size && v >= size * (size - 1) && color == Player::RED)
            adjacentHexagons.push_back(std::make_pair(size * size + 1, 1));
        if ((v + 1) % size == 0 && color == Player::BLUE)
            adjacentHexagons.push_back(std::make_pair(size * size + 3, 1));

    }
    return adjacentHexagons.cbegin();
}

typename std::vector<std::pair<int,int>>::const_iterator HexGraph::cend() const {
    return adjacentHexagons.cend();
}

void HexGraph::computePaths(int source, std::vector<int> &dist, std::vector<int> &pred) const
{
    int n = size();
    dist.clear();
    dist.resize(n, std::numeric_limits<int>::max());
    dist[source] = 0;
    pred.clear();
    pred.resize(n, -1);
    std::set<std::pair<int, int>> pq;
    pq.insert(std::make_pair(dist[source], source));
 
    while (!pq.empty()) 
    {
        int distance = pq.begin()->first;
        int u = pq.begin()->second;
        pq.erase(pq.begin());
 
        for (auto it = cbegin(u); it != cend(); it++)
        {
            std::pair<int,int> neighbour = *it;
            int v = neighbour.first;
            int newDistance = distance + neighbour.second;
	    if (newDistance < dist[v]) {
	        pq.erase(std::make_pair(dist[v], v));
 
	        dist[v] = newDistance;
	        pred[v] = u;
	        pq.insert(std::make_pair(dist[v], v));
	    }
        }
    }
}

std::list<int> HexGraph::findShortestPath(int source, int dest) const
{
    std::vector<int> dist;
    std::vector<int> pred;
    std::list<int> path;

    computePaths(source, dist, pred);
    if (pred[dest] != -1)
        for ( ; dest != -1; dest = pred[dest])
            path.push_front(dest);
    return path;
}

int HexGraph::findShortestPathLength(int source, int dest) const
{
    std::vector<int> dist;
    std::vector<int> pred;

    computePaths(source, dist, pred);
    if (pred[dest] == -1)
        return -1;
    return dist[dest];
}

int HexGraph::size() const 
{ 
    return board.size * board.size + 4; 
}


// move.h
// Aswin van Woudenberg

#ifndef MOVE_H
#define MOVE_H

#include <utility>
#include <iostream>

#include "state.h"

using Move = std::pair<int,int>;

std::ostream &operator<<(std::ostream &os, const Move &m);
std::istream &operator>>(std::istream &is, Move &m);

#endif // MOVE_H

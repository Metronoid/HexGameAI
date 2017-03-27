// move.cpp
// Aswin van Woudenberg

#include "move.h"
#include "state.h"

#include <vector>
#include <utility>

std::ostream &operator<<(std::ostream &os, const Move &m)
{
    if (m.second + 1 > 26) os << static_cast<char>('A' + (m.second + 1) / 26 - 1);
    os << static_cast<char>('A' + (m.second + 1) % 26 - 1) << m.first + 1; 
    return os;
}

std::istream &operator>>(std::istream &is, Move &m)
{
    int row = 0, col = 0;
    char c;

    c = is.get();
    while (!((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z'))) {
        c = is.get();
    }
    while ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z')) {
        if (c >= 'A' && c <= 'Z') 
            col = col * 26 + (c - 'A' + 1);
        if (c >= 'a' && c <= 'z')
            col = col * 26 + (c - 'a' + 1);
        c = is.get();
        std::cerr << col << std::endl;
    }
    is.putback(c);
    is >> row;
    m.first = row - 1;
    m.second = col - 1;
    
    return is;            
}



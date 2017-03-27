// ansi.cpp
// Aswin van Woudenberg

#include "ansi.h"

#ifndef __linux__

std::ostream &operator<<(std::ostream &os, const Color &c)
{
    return os;
}

#else

std::ostream &operator<<(std::ostream &os, const Color &c)
{
    static int lastForeground = 0;
    static int lastBackground = 0;
	
    if (c.layer == ColorLayer::BACKGROUND)
        lastBackground = (c.color != ColorValue::DEFAULT ? 40 + static_cast<int>(c.color) : 0);
    else
        lastForeground = (c.color != ColorValue::DEFAULT ? 30 + static_cast<int>(c.color) : 0);

    bool bold = (c.layer == ColorLayer::FOREGROUND ? (c.weight == ColorWeight::BOLD) : false);
    os << "\033[" << (bold ? 1 : 0);
    if (!(bold && lastForeground == 0)) 
        os << ';' << lastForeground;
    if (lastBackground != 0)
        os << ';' << lastBackground;
    return (os << 'm');
}

#endif

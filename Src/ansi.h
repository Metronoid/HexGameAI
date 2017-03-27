// ansi.h
// Aswin van Woudenberg

#ifndef ANSI_H
#define ANSI_H

#include <ostream>

enum class ColorValue { BLACK, RED, GREEN, YELLOW, BLUE, MAGENTA, CYAN, WHITE, DEFAULT };
enum class ColorLayer { FOREGROUND, BACKGROUND };
enum class ColorWeight { NORMAL, BOLD };

struct Color
{
    const ColorValue color;
    const ColorLayer layer;
    const ColorWeight weight;

    Color(ColorValue color = ColorValue::DEFAULT, ColorLayer layer = ColorLayer::FOREGROUND, 
        ColorWeight weight = ColorWeight::NORMAL): color(color), layer(layer), 
        weight(weight) { }
    Color(ColorValue color, ColorWeight weight):
        color(color), layer(ColorLayer::FOREGROUND), weight(weight) { }
    friend std::ostream &operator<<(std::ostream &os, const Color &c);
};


#endif // ANSI_H

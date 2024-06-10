#pragma once

#include "global.hpp"

enum class Color {
    DEFAULT,
    RED,
    GREEN,
    BLUE,
    YELLOW,
    CYAN,
    MAGENTA,
    WHITE
};

void setColor(Color color);

inline void ColorPrint(Color color, const std::string& text) {
    setColor(color);
    std::cout << text << std::endl;
    setColor(Color::DEFAULT);
}
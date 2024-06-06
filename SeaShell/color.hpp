#pragma once

#include "../global.hpp"

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
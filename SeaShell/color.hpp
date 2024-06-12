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

template<typename T>
void Print(T arg) {
    std::cout << arg;
}

// Recursive template function to print multiple arguments
template<typename T, typename... Args>
void Print(T firstArg, Args... args) {
    if constexpr (std::is_same_v<T, Color>) {
        setColor(firstArg);
        Print(args...);
        setColor(Color::DEFAULT); // Reset color to default after printing
    } else {
        std::cout << firstArg << " ";
        Print(args...);
    }
}

